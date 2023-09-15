/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 03:08:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 17:41:49 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	special_case_expand(t_token **token)
{
	int	i;

	i = 0;
	if ((*token)->str && (*token)->str[1] && (*token)->str[1] == '?')
	{
		tracked_free((*token)->str);
		(*token)->str = ft_itoa(g_error);
		if (!(*token)->str)
			return (ERROR);
		return (SUCCESS);
	}
	else if ((*token)->str && (is_num((*token)->str[1]) == 1
			|| (*token)->str[1] == '$'))
	{
		if ((*token)->str[i + 2] == '\0')
			return (tracked_free((*token)->str), (*token)->str = NULL, 0);
		while ((*token)->str[i + 1])
		{
			(*token)->str[i] = (*token)->str[i + 2];
			i++;
		}
		return (SUCCESS);
	}
	return (ERROR);
}

void	check_heredoc(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			while (tmp && is_type_wq(tmp))
			{
				tmp->type = S_QUOTES;
				tmp = tmp->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}

int	expand(t_token **token, t_env **env)
{
	if (!(*token)->next && (*token)->str == NULL && !is_op((*token)))
		return (cmd_not_found((*token)->str), SUCCESS);
	check_heredoc(token);
	if (expand_d_quotes(token, *env) == ERROR)
		return (ERROR);
	if (expand_to_token(token, env) == ERROR)
		return (ERROR);
	while (!is_token_ok(*token))
	{
		if (clean_token(token) == NEW_LINE)
			return (NEW_LINE);
		if (clean_token(token) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
