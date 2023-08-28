/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:56:24 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 01:14:05 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int space_only(char *input)
{
	int i;

	i = 0;
	if (input != NULL)
	{
		while (input[i])
		{
			if (ft_isspace(input[i]))
				i++;
			else
				return (1);
		}
		return (0);
	}
	else
		return (0);
}

int check_end_token(t_token *lst_token)
{
	t_token *tmp;

	tmp = lst_token;
	if (tmp->next == NULL)
	{
		if (is_operator(tmp) || tmp->type == PIPE)
			return (err_end_token(tmp), NEW_LINE); // FREE
		else
			return (SUCCESS);
	}
	while (tmp->next->next)
		tmp = tmp->next;
	if (tmp->next->type == SEPARATOR)
	{
		free(tmp->next);
		tmp->next = NULL;
		return (SUCCESS);
	}
	if (is_operator(tmp->next) || tmp->next->type == PIPE)
		return (err_end_token(tmp->next), NEW_LINE); // FREE
	return (SUCCESS);
}

int parsing(char *input, t_token **list_token)
{
	*list_token = NULL;
	if (fill_tokens(input, list_token) == ERROR)
		return (ERROR);
	if (input)
		free(input);
	if (check_end_token(*list_token) == ERROR)
		return (ERROR);
	if (operator_mod(*list_token) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
