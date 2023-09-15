/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_remake.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:43:24 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 15:39:19 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\'')
		while (str[i + 1] && str[i + 1] != '\'')
			i++;
	else if (str[0] == '"')
		while (str[i + 1] && str[i + 1] != '"')
			i++;
	if (!str[i + 1])
		return (-1);
	return (i);
}

int	ft_strlen_word(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		i++;
	if (str[i] == '?')
		return (++i);
	while (str[i] && !is_sep_op(str[i]))
	{
		if (str[0] == '$' && str[i] && !is_alnum_und(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_strlen_remake(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '\'' || str[0] == '"')
		return (ft_strlen_quotes(str));
	else
		return (ft_strlen_word(str));
	return (i);
}
