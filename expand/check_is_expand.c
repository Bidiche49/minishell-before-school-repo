/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 01:14:15 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 00:30:26 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	isexpand_ok(t_token *list_token)
{
	while (list_token)
	{
		if (is_an_exp_dquotes(list_token) == 1)
			return (0);
		list_token = list_token->next;
	}
	return (1);
}

int	is_an_exp_dquotes(t_token *list_token)
{
	int	i;

	i = 0;
	if (list_token->type == D_QUOTES)
	{
		while (list_token->str && list_token->str[i])
		{
			if (list_token->str[i + 1] && list_token->str[i] == '$'
				&& (list_token->str[i + 1] == '$' || list_token->str[i + 1] == '?'))
				return (1);
			if (list_token->str[i + 1] && list_token->str[i] == '$'
				&& is_alnum_und(list_token->str[i + 1]))
				return (1);
			i++;
		}
	}
	return (0);
}
