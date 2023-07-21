/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:38:17 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/21 22:41:40 by ntardy           ###   ########.fr       */
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
