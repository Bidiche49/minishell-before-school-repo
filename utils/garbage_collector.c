/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:42:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 02:19:31 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_fd_garbage	**get_fd_garbage(void)
{
	static t_fd_garbage	*fd_garbage = NULL;
	return (&fd_garbage);
}

void	tracked_close(int fd)
{
	t_fd_garbage **fd_garbages;
	t_fd_garbage *current;
	t_fd_garbage *prev ;

	if (!fd || is_fd_open(fd) == 1)
		return ;
	fd_garbages = get_fd_garbage();
	current = *fd_garbages;
	prev = NULL;
	while (current)
	{
		if (current && current->fd && current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else if (current->next)
				(*fd_garbages) = current->next;
			if (current)
			{
				if (current->fd && is_fd_open(current->fd) != 1)
					close(current->fd);
			}
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_garbage	**get_garbage(void)
{
	static t_garbage	*garbage = NULL;
	return (&garbage);
}

void tracked_free(void *ptr)
{
	t_garbage **garbages;
	t_garbage *current;
	t_garbage *prev ;

	if (!ptr)
		return ;
	garbages = get_garbage();
	current = *garbages;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				(*garbages) = current->next;
			free(current->ptr);
			current->ptr = NULL;
			free(current);
			current = NULL;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	collect_fd()
{
	t_fd_garbage *fd_current;

	fd_current = *get_fd_garbage();
	while (fd_current)
	{
		if (is_fd_open(fd_current->fd) != 1)
			close(fd_current->fd);
		fd_current = fd_current->next;
	}
	*get_fd_garbage() = NULL;
}

void collect_ptr()
{
	t_garbage *current;
	t_garbage *next;

	next = NULL;
	current = *get_garbage();
	while (current)
	{
		next = current->next;
		if (current->ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		free(current);
		current = NULL;
		current = next;
	}
	*get_garbage() = NULL;
}
void	garbage_collect()
{
	collect_fd();
	collect_ptr();
}
