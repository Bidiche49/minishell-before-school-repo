/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 01:16:15 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/07 11:11:10 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	clean_first_token(t_token **list_token)
{
	t_token	*tmp;

	tmp = *list_token;
	(*list_token) = (*list_token)->next;
	if (tmp->str)
		free(tmp->str);
	free(tmp);
}

void	del_next_token(t_token **token)
{
	t_token	*tmp;

	if (!(*token)->next)
		return ;
	tmp = (*token)->next->next;
	if ((*token)->next->str)
		free((*token)->next->str);
	free((*token)->next);
	(*token)->next = tmp;
}

void	del_all_token(t_token **list_token)
{
	t_token	*tmp;

	tmp = *list_token;
	while (tmp->next)
		del_next_token(&tmp);
	tmp->type = WORD;
	if (tmp->str)
		free(tmp->str);
	tmp->str = NULL;
}

int	if_forest_clean_token(t_token *tok)
{
	if (tok->next && tok->next->type == SEPARATOR && ((!tok->next->next)
		|| (tok->next->next && tok->next->next->type == PIPE)))
		del_next_token(&tok);
	if (tok->next && tok->next->type == WORD && !tok->next->str)
		del_next_token(&tok);
	if (tok->next && tok->next->type == D_QUOTES && !tok->next->str)
		del_next_token(&tok);
	if (tok->next && tok->next->type == S_QUOTES && !tok->next->str)
		del_next_token(&tok);
	if (tok->next && tok->type == SEPARATOR
		&& tok->next->type == SEPARATOR)
		del_next_token(&tok);
	if (is_op(tok) && (!tok->next || (tok->next
				&& !tok->next->next && tok->next->type == SEPARATOR)))
		return (err_end_token(NULL), NEW_LINE);
	if (dble_op(tok))
		return (err_end_token(tok), NEW_LINE);
	return (SUCCESS);
}

int	clean_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (first_tok_null(*token) == 0)
		clean_first_token(token);
	while (tmp)
	{
		if (!is_sep_pipe(tmp) && tmp->next && is_type_wq(tmp->next))
			if (cat_word(tmp) == ERROR)
				return (ERROR);
		tmp = tmp ->next;
	}
	tmp = *token;
	while (tmp)
	{
		if (if_forest_clean_token(tmp) == NEW_LINE)
			return (del_all_token(token), NEW_LINE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
