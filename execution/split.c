/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:18:18 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/22 10:51:39 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;
	int		size;

	size = 0;
	while (s[size])
		size++;
	str = malloc(sizeof (char) * (size + 1));
	i = 0;
	if (str == 0)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	y;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	y = 0;
	while (s[i])
	{
		if (i >= start && y < len)
		{
			str[y++] = s[i];
		}
		i++;
	}
	str[y] = '\0';
	return (str);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	words;

	words = 0;
	if (ft_strlen(s) == 0)
		return (0);
	if (s[0] != c)
		words++;
	i = 1;
	while (s[i])
	{
		if ((s[i] != c) && (s[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

static int	ft_size(char const *s, char c, int i)
{
	int	x;

	x = 0;
	while (s[i] != c && s[i] != '\0')
	{
		x++;
		i++;
	}
	return (x);
}

static void	*ft_free(char **s, int j)
{
	while (j >= 0)
	{
		free(s[j]);
		j--;
	}
	free(s);
	return (0);
}

static char	**ft_empty_malloc(void)
{
	char	**dest;

	dest = malloc(sizeof(char *) * 1);
	dest[0] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		j;
	int		start;

	start = 0;
	if (s == NULL || ft_strlen(s) == 0)
		return (ft_empty_malloc());
	dest = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (dest == 0)
		return (0);
	j = -1;
	while (s[start] == c)
		start++;
	while (++j < ft_count(s, c) + 1 && start < (int)ft_strlen(s))
	{
		dest[j] = ft_substr(s, start, ft_size(s, c, start));
		if (dest[j] == 0)
			ft_free(dest, j);
		start += ft_size(s, c, start);
		while (s[start] == c)
			start++;
	}
	dest[j] = NULL;
	return (dest);
}