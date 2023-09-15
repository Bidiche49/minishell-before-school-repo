/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:45:47 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 20:48:12 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_fd_garbage	**get_fd_garbage(void)
{
	static t_fd_garbage	*fd_garbage = NULL;

	return (&fd_garbage);
}

int	is_fd_open(int fd)
{
	return (!access("/proc/self/fd/%d", fd));
}

void	add_fd_garbage(int fd)
{
	t_fd_garbage		**fd_garbages;
	t_fd_garbage		*current;
	t_fd_garbage		*new;

	fd_garbages = get_fd_garbage();
	current = *fd_garbages;
	if (fd == -1)
		return ;
	while (current)
	{
		if (current->fd == fd)
			return ;
		current = current->next;
	}
	new = ft_calloc(sizeof(t_fd_garbage), 1);
	if (!new)
		return ;
	new->fd = fd;
	new->next = (*fd_garbages);
	(*fd_garbages) = new;
}

int	tracked_open(char *str, int first, int second, int third)
{
	int	fd;

	if (!str)
		return (-1);
	if (second == -1 && third == -1)
		fd = open(str, first);
	else if (third == -1)
		fd = open(str, first | second);
	else
		fd = open(str, first | second | third, 0644);
	if (fd == -1)
		return (-1);
	add_fd_garbage(fd);
	return (fd);
}

void	tracked_close(int fd)
{
	t_fd_garbage	**fd_garbages;
	t_fd_garbage	*current;
	t_fd_garbage	*prev ;

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
				if (current->fd && is_fd_open(current->fd) != 1)
					close(current->fd);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
