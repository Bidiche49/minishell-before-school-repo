/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:32:50 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 00:37:15 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

void	convert_file(int x, int y)
{
	dup2(y, 1);
	dup2(x, 0);
}

int	open_all(t_section *section, t_token *token)
{
	if (token->type == OUT)
		section->fd[1] = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (token->type == APPEND)
		section->fd[1] = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (token->type == IN || token->type == HEREDOC)
		section->fd[0] = open(token->str, O_RDONLY);
	if (section->fd[0] == -1 || section->fd[1] == -1)
		return (0);
	return (1);
}

int file_open(t_section *section)
{
	t_token *token;

	token = section->token;
	while (token)
	{
		if (token->type == SEPARATOR)
			token = token->next;
		if (open_all(section, token) == 0)
			return (0);
		if (token->next && token->next->type != HEREDOC && token->next->type != IN && token->type != HEREDOC && token->type != IN)
			close (section->fd[1]);
		if (token->next && token->next->type == IN && token->next->type == HEREDOC && token->type == IN && token->type == HEREDOC)
			close (section->fd[0]);
		token = token->next;
	}
	return (1);
}

int	assigne_file(t_section *section, int *j, int i)
{
	
	i = file_open(section);
	if (i >= 1)
		i = util_dup2(section, j[0], j[1]);
	return (i);
}