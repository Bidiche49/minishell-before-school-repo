/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:31:21 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/30 02:16:41 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *next_token(char *str)
{
	if (ft_isspace(*str))
	{
		while (*str && ft_isspace(*str))
			str++;
		return (str);
	}
	if (*str == '>' && *(str + 1) && *(str + 1) == '>')
		return (str + 2);
	if (*str == '<' && *(str + 1) && *(str + 1) == '<')
		return (str + 2);
	if (*str == '<')
		return (str + 1);
	if (*str == '>')
		return (str + 1);
	if (*str == '|')
		return (str + 1);
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		str++;
		return (str);
	}
	if (*str == '\'')
	{
		str++;
		while (*str && *str != '\'')
			str++;
		str++;
		return (str);
	}
	if (*str == '$')
	{
		str++;
		while (*str && !is_sep_op(*str))
			str++;
		return (str);
	}
	else
	{
		while (*str && !is_sep_op(*str))
			str++;
		return (str);
	}
}

int fill_tokens(char *input, t_token **list_token)
{
	char *tmp_input;
	t_token *new_token;

	tmp_input = input;
	while (*tmp_input && ft_isspace(*tmp_input))
		tmp_input++;
	while (*tmp_input)
	{
		new_token = ft_newtoken(tmp_input);
		// printf("new_token->str = %s\n", new_token->str);
		if (ft_lstadd_back(list_token, new_token) == ERROR)
			return (ERROR); /////////////////////FREE
		tmp_input = next_token(tmp_input);
	}

	return (SUCCESS);
}
