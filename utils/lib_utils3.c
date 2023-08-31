/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 04:36:31 by audrye            #+#    #+#             */
/*   Updated: 2023/08/31 07:11:29 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ram;
	int		len;

	if (s1 == NULL)
	{
		ram = ft_strdup(s2);
		return (free(s2), ram);
	}
	else if (s2 == NULL)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	ram = malloc(sizeof(char) * (len + 1));
	if (!ram)
		return (NULL);
	ft_strcpy(ram, s1);
	ft_strcpy(&ram[ft_strlen(s1)], s2);
	return (ram);
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
	unsigned char	*dst;

	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	dst = malloc(size * nmemb);
	if (!dst)
		return (NULL);
	ft_bzero(dst, (size * nmemb));
	return (dst);
}
