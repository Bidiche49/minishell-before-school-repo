/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:38:17 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 02:24:47 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*first_word(char *str)
{
	char	*first_word;
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]) == 0 && str[i] != '|')
		i++;
	first_word = ft_calloc((i + 1), sizeof(char));
	if (first_word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]) == 0 && str[i] != '|')
	{
		first_word[i] = str[i];
		i++;
	}
	return (first_word);
}

char	*ft_strdup(const char *src)
{
	unsigned int	i;
	char			*str;

	i = -1;
	if (!src)
		return (NULL);
	str = ft_calloc((ft_strlen(src) + 1),sizeof(char));
	if (!str)
		return (NULL);
	while (src[++i])
		str[i] = src[i];
	return (str);
}

char	*ft_strcat_dup(char *dest, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(dest);
	if (!tmp)
		return (NULL);
	if (dest)
		tracked_free(dest);
	dest = ft_calloc((ft_strlen(tmp) + ft_strlen(str) + 1), sizeof(char));
	if (!dest)
		return (tracked_free(tmp), NULL);
	while (tmp && tmp[j])
	{
		dest[j] = tmp[j];
		j++;
	}
	if (tmp)
		tracked_free(tmp);
	while (str[i])
		dest[j++] = str[i++];
	return (dest);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*str;
	int	i;
	int	y;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = ft_calloc((len + 1), sizeof (char));
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

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alnum_und(char c)
{
	if (is_num(c) || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}
