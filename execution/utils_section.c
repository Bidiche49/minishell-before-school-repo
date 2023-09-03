/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:06:50 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 00:07:02 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_word(int type)
{
	if (type == WORD || type == S_QUOTES || type == D_QUOTES)
		return (1);
	return (0);		
}

int	is_redir(int type)
{
	if (type == IN || type == OUT || type == APPEND || type == HEREDOC)
		return (1);
	return (0);		
}

int	count_section(t_token *token)
{
	int	i;
	
	i = 1;
	while (token)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i);
}