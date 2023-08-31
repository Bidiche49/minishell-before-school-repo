/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:13:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/31 10:49:26 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	count_word;

	i = 0;
	count_word = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count_word++;
		i++;
	}
	return (count_word);
}

static int	ft_lenword(const char *s, char c, int i)
{
	int	len_word;

	len_word = 0;
	while (s[i] && (s[i++] != c))
		len_word++;
	return (len_word);
}

static char	**ft_freemobile(char **res, int k)
{
	while (k > 0)
		free(res[k--]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		k;
	int		count_word;

	count_word = ft_countword(s, c);
	i = 0;
	k = -1;
	if (!s)
		return (NULL);
	res = ft_calloc((count_word + 1), sizeof(char *));
	if (res == NULL)
		return (malloc_error(), NULL);
	while (s[i] && ++k < count_word)
	{
		while (s[i] == c)
			i++;
		res[k] = ft_substr(s, i, ft_lenword(s, c, i));
		if (!res[k])
			return (ft_freemobile(res, k));
		i += ft_lenword(s, c, i);
	}
	return (res);
}

