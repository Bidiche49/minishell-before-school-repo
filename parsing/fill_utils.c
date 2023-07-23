/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:34:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 23:58:11 by ntardy           ###   ########.fr       */
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
	if (ft_isspace(input[i]))
		i++;
	while (input[i] && input[i] != '|')
	{
		if (ft_isspace(input[i]) && (input[i + 1] == '\0' || input[i + 1] == '|'))
				break ;
		len++;
		i++;
	}
	printf("len malloc_option = %d\n", len);
	list_token->options = malloc(sizeof(char) * (len + 1));
	if (list_token->options == NULL)
		return (ft_error(", malloc KO !"));
	return (0);
}
