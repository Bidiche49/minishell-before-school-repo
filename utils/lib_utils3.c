/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 04:36:31 by audrye            #+#    #+#             */
/*   Updated: 2023/09/14 12:11:34 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char		*res;
	int			i;
	int const	j = ft_strlen(s1);

	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (s1);
	res = ft_calloc((j + ft_strlen(s2) + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i =  -1;
	while (s2[++i])
		res[j + i] = s2[i];
	return (res);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cast_s;
	size_t			i;

	i = 0;
	cast_s = (unsigned char *)s;
	while (i < n)
	{
		cast_s[i] = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	t_garbage		**garbages;
	t_garbage		*new;

	garbages = get_garbage();
	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (malloc_error(), NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (malloc_error(), NULL);
	new->ptr = ptr;
	new->next = (*garbages);
	(*garbages) = new;
	ft_bzero(ptr, (size * nmemb));
	return (ptr);
}

t_token	*lst_last(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
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
	int				fd;

	if (!str)
		return (-1);
	if (second == -1 && third == -1)
		fd = open(str, first);
	else
		fd = open(str, first | second | third, 0644);
	if (fd == -1)
		return (-1);
	add_fd_garbage(fd);
	return (fd);
}
