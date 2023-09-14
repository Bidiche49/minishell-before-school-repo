/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 06:06:16 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 09:02:12 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	openfiles(t_token *token)
{
	int fd;

	fd = -1;
	while (token && token->type != PIPE)
	{
		if (is_redir(token->type))
		{
			if (token->type == OUT)
				fd = tracked_open(token->str, O_CREAT, O_WRONLY, O_TRUNC);
			if (token->type == APPEND)
				fd = tracked_open(token->str, O_CREAT, O_WRONLY, O_APPEND);
			if (token->type == IN)
				fd = tracked_open(token->str, O_RDONLY, -1, -1);
			if (token->type == HEREDOC)
				fd = tracked_open("/tmp/.heredoc", O_RDONLY, -1, -1);
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

	fd = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == OUT || token->type == IN || token->type == APPEND)
		{
			if (token->type == OUT)
				fd = tracked_open(token->str, O_CREAT, O_WRONLY, O_TRUNC);
			if (token->type == APPEND)
				fd = tracked_open(token->str, O_CREAT, O_WRONLY, O_APPEND);
			if (token->type == IN)
				fd = tracked_open(token->str, O_RDONLY, -1, -1);
			if (token->type == HEREDOC)
				fd = tracked_open("/tmp/.heredoc", O_RDONLY, -1, -1);
			if (fd < 0)
				return (error_redir(token->str, 0), -1);
			if (token->type == OUT || token->type == APPEND)
				dup2(fd, STDOUT_FILENO);
			else
				dup2(fd, STDIN_FILENO);
		}
		token = token->next;
	}
	return (fd);
}
