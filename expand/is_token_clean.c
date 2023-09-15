/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 01:17:14 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 23:18:15 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	first_tok_null(t_token *tok)
{
	if (tok->next && is_type_wq(tok) && !tok->str
		&& is_type_wq(tok->next) && tok->next->str)
		return (0);
	if (tok->next && is_type_wq(tok) && !tok->str
		&& tok->next->type == SEPARATOR && tok->next->next
		&& is_type_wq(tok->next->next) && tok->next->next->str)
		return (0);
	if (tok->next && tok->type == SEPARATOR
		&& is_type_wq(tok->next) && tok->next->str)
		return (0);
	return (1);
}

int	dble_op(t_token *tok)
{
	if (tok->next && is_op(tok))
	{
		if (tok->str)
			return (0);
		if (is_op(tok->next))
			return (1);
		if (tok->next->next && is_op(tok->next->next)
			&& tok->next->type == SEPARATOR)
			return (1);
	}
	return (0);
}

int	if_forest_is_token_ok(t_token *tok)
{
	if (tok->next && tok->next->type == WORD
		&& tok->next->str == NULL)
		return (0);
	else if (tok->next && tok->next->type == D_QUOTES
		&& tok->next->str == NULL)
		return (0);
	else if (tok->next && tok->next->type == S_QUOTES
		&& tok->next->str == NULL)
		return (0);
	else if (!tok->next && tok->type == SEPARATOR)
		return (0);
	else if (tok && !is_sep_pipe(tok)
		&& tok->next && is_type_wq(tok->next))
		return (0);
	else if (tok->next && tok->type == SEPARATOR
		&& tok->next->type == SEPARATOR)
		return (0);
	else if (is_op(tok)
		&& !tok->str && ((!tok->next && !tok->str)
			|| (tok->next && !tok->next->next
				&& tok->next->type == SEPARATOR)))
		return (0);
	return (1);
}

int	is_token_ok(t_token *tok)
{
	if (is_type_wq(tok))
		tok->type = WORD;
	if (first_tok_null(tok) == 0)
		return (0);
	if (tok && tok->type == PIPE)
		return (0);
	while (tok)
	{
		if (is_type_wq(tok))
			tok->type = WORD;
		if (!if_forest_is_token_ok(tok))
			return (0);
		if (tok->type == SEPARATOR && tok->next && tok->next->type == PIPE)
			return (0);
		if (dble_op(tok))
			return (0);
		tok = tok->next;
	}
	return (1);
}
