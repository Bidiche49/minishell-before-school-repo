/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:42:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 12:15:47 by ntardy           ###   ########.fr       */
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

	if (!fd)
		return ;
	fd_garbages = get_fd_garbage();
	current = *fd_garbages;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else if (current->next)
				(*fd_garbages) = current->next;
			if (current)
			{
				if (current->fd && current->fd != -1)
				{
					close(current->fd);
					current->fd = -1;
				}
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
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	collect_fd()
{
	t_fd_garbage **fd_garbages;
	t_fd_garbage *fd_current;
	t_fd_garbage *fd_tmp;

	fd_garbages = get_fd_garbage();
	fd_current = *fd_garbages;
	while (fd_current)
	{
		fd_tmp = fd_current;
		if (fd_current->next)
			fd_current = fd_current->next;
		else
		{
			close(fd_tmp->fd);
			// free(fd_tmp);
			fd_garbages = NULL;
			break ;
		}
		close(fd_tmp->fd);
		// free(fd_tmp);
	}
}

void	collect_ptr()
{
	t_garbage *current;
	t_garbage *tmp;


	current = *get_garbage();
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->ptr);
		free(tmp);
	}
}
void	garbage_collect()
{
	collect_ptr();
	collect_fd();
}
