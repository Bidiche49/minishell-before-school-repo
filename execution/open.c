/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 06:06:16 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/13 06:12:02 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	openfiles(t_token *token)
{
	int fd;

	fd = -1;
	while (token && token->type != PIPE)
	{
		if (token->type == OUT || token->type == IN || token->type == APPEND)
		{
			if (token->type == OUT)
				fd = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (token->type == APPEND)
				fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (token->type == IN || token->type == HEREDOC)
				fd = open(token->str, O_RDONLY);
			if (fd < 0)
				return (error_redir(token->str, 1));
			if (token->type == OUT || token->type == APPEND)
				dup2(fd, STDOUT_FILENO);
			else
				dup2(fd, STDIN_FILENO);
		}
		token = token->next;
	}
	return (fd);
}

int	openfiles_builtins(t_token *token)
{
	int fd;

	fd = -1;
	while (token && token->type != PIPE)
	{
		if (token->type == OUT || token->type == IN || token->type == APPEND)
		{
			if (token->type == OUT)
				fd = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (token->type == APPEND)
				fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (token->type == IN || token->type == HEREDOC)
				fd = open(token->str, O_RDONLY);
			if (fd < 0)
				return (error_redir(token->str, 0));
			if (token->type == OUT || token->type == APPEND)
				dup2(fd, STDOUT_FILENO);
			else
				dup2(fd, STDIN_FILENO);
		}
		token = token->next;
	}
	return (fd);
}
