/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:39:10 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 00:54:35 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void first_close_cmd(t_section *section, int n, int j)
{
	if (section->fd[0] != j)
		close(section->fd[0]);
	if (section->next)
	{
		if (n == 1)
			close(section->next->pipe[0]);
		if (section->next->pipe[1] != section->fd[1])
			close(section->next->pipe[1]);
	}
	close(section->fd[1]);
}

void last_close_cmd(t_section *section)
{
	close(section->fd[1]);
	close(section->pipe[1]);
	if (section->pipe[0] != section->fd[0])
		close(section->pipe[0]);
	close(section->fd[0]);
}

void other_close_cmd(t_section *section, int n)
{
	close(section->pipe[1]);
	if (n == 1)
		close(section->next->pipe[0]);
	if (section->pipe[0] != section->fd[0])
		close(section->pipe[0]);
	if (section->next->pipe[1] != section->fd[1])
		close(section->next->pipe[1]);
	close(section->fd[0]);
	close(section->fd[1]);
}

void	fork_close(t_section *section, int *pid, int *j)
{
	free(pid);
	convert_file(section->fd[0], section->fd[1]);
	while (section)
	{
		if (section->deep == 0)
			first_close_cmd(section, 1, j[0]);
		else if (section->next == NULL && section->deep != 0)
			last_close_cmd(section);
		else
			other_close_cmd(section, 1);
		section = section->next;
	}
	close(j[0]);
	close(j[1]);
}

t_section	*next_section(t_section *section, int x, int *i)
{
	if (section->next && i == 0)
		*i = 1;
	if (section->deep == 0)
		first_close_cmd(section, 0, x);
	else if (section->next == NULL && section->deep != 0)
		last_close_cmd(section);
	else
		other_close_cmd(section, 0);
	return (section->next);
}