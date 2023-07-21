/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:13:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/21 22:49:22 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	char	*tmp_s;
	char	*res;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	tmp_s = (char *)s;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	res = malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	while ((start + i) < ft_strlen(s) && i < len)
	{
		res[i] = tmp_s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

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

char	**ft_split_pars(char const *s, char c)
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
	res = malloc(sizeof(char *) * (count_word + 1));
	if (res == NULL)
		return (printf("malloc KO\n"),NULL);
	res[count_word] = NULL;
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

