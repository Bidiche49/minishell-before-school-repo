/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 04:36:31 by audrye            #+#    #+#             */
/*   Updated: 2023/08/31 00:05:53 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*ft_strcpy(char *s1, char const *s2)
// {

// }

char	*ft_strjoin(char *str1, const char *str2)
{
	char	*res;
	int		i;
	int		j;
	
	if (!str1)
	{
		res = ft_strdup(str2);
		if (!res)
			return (NULL);
		return (res);
	}
	if (!str2)
		return (str1);
	res = calloc((ft_strlen(str1) + ft_strlen(str2) + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
		res[j++] = str1[i++];
	i = 0;
	while (str2[i])
		res[j++] = str2[i++];
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
	unsigned char	*dst;

	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	dst = malloc(size * nmemb);
	if (!dst)
		return (NULL);
	ft_bzero(dst, (size * nmemb));
	return (dst);
}
