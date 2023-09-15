/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:56:24 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 23:20:05 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int space_only(char *input)
{
	int i;

	i = 0;
	if (input != NULL)
	{
		if (input[0] && input[1] && !input[2] && input[0] == '\\' && input[1] == 'n')
			return (1);
		if(input[0] && ft_isspecial(input[0]))
			return (1);
		while (input[i])
		{
			if (ft_isspace(input[i]) || input[i] == '#')
				i++;
			else if (input[i] && !ft_isspace(input[i]))
				return (0);
		}
		return (1);
	}
	else
		return (1);
}

int check_end_token(t_token *lst_token)
{
	t_token *tmp;

	tmp = lst_token;
	if (tmp->next == NULL)
		return (SUCCESS);
	while (tmp->next->next)
		tmp = tmp->next;
	if (tmp->next->type == SEPARATOR)
	{
		tracked_free(tmp->next);
		tmp->next = NULL;
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	is_forbidden_char(char c)
{
	if (c == '&' || c == '(' || c == ')' || c == ';')
		return (1);
	return (0);
}

int	check_forbidden_char(t_token *token)
{
	int	i;

	i = 0;
	if (token && (!token->str || token->type != WORD))
		return (0);
	while (token->str[i])
	{
		if (is_forbidden_char(token->str[i]))
		{
			msg(ERR_END_TOKEN);
			if (token->str[i + 1] && token->str[i + 1] == token->str[i]
				&& token->str[i] != '(' && token->str[i] != ')')
				write(STDERR_FILENO, &token->str[i], 1);
			write(STDERR_FILENO, &token->str[i], 1);
			msg("'\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing(char *input, t_token **token, t_env **env)
{
	int	return_val;
	t_token	*tmp;

	*token = NULL;
	return_val = fill_tokens(input, token);
	if (input)
		free(input);
	if (return_val == ERROR)
		return (ERROR);
	if (return_val == NEW_LINE)
		return (NEW_LINE);
	if (operator_mod(*token) == ERROR)
		return (ERROR);
	tmp = *token;
	while (tmp)
	{
		if (check_forbidden_char(tmp))
			return (NEW_LINE);
		tmp = tmp->next;
	}
	return (expand(token, env));
}
