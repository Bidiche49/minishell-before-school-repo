/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:38:17 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 16:40:45 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*first_word(char *str)
{
	char	*first_word;
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '|')
		i++;
	first_word = malloc(sizeof(char) * (i + 1));
	if (first_word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '|')
	{
		first_word[i] = str[i];
		i++;
	}
	first_word[i] = '\0';
	return (first_word);
}

char	*ft_strdup(const char *src)
{
	unsigned int	i;
	char			*str;

	i = -1;
	str = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (str == NULL)
		return (NULL);
	while (src[++i])
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}

int	ft_strcat_pars(char *abs_path, char *path, char *cmd, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i])
		abs_path[j++] = path[i++];
	abs_path[j++] = sep;
	i = 0;
	while (cmd[i])
		abs_path[j++] = cmd[i++];
	abs_path[j] = '\0';
	return (0);
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
