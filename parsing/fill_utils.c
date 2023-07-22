/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:34:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 15:43:04 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	calc_i(char *input, int token_passed)
{
	int	i;

	i = 0;
	while (token_passed > 0)
	{
		while (input[i])
		{
			i++;
			if (input[i] && input[i - 1] == '|')
			{
				token_passed--;
				break ;
			}
		}
	}
	return (i);
}

int	malloc_option(t_token *list_token, char *input, int i)
{
	int	len;

	len = 0;
	while (input[i] == ' ')
		i++;
	while (input[i] && input[i] != '|')
	{
		if (input[i] == ' ')
		{
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0' || input[i] == '|')
				break ;
			len++;
		}
		len++;
		i++;
	}
	list_token->options = malloc(sizeof(char) * (len + 1));
	if (list_token->options == NULL)
		return (ft_error(", malloc KO !"));
	return (0);
}
