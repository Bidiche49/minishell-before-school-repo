/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:16:41 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/31 10:12:29 by ntardy           ###   ########.fr       */
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
int	is_op(t_token *token)
{
	if (token->type == OUT || token->type == IN || token->type == HEREDOC
		|| token->type == APPEND || token->type == PIPE)
		return (1);
	return (0);
}

int	is_type_wq(t_token *token)
{
	if (token->type == WORD || token->type == S_QUOTES || token->type == D_QUOTES)
		return (1);
	return (0);
}

void	err_end_token(t_token *token)
{
	msg(ERR_END_TOKEN);
	if (token->type	== PIPE)
		msg("|'\n");
	if (token->type	== IN)
		msg("<'\n");
	if (token->type	== OUT)
		msg(">'\n");
	if (token->type	== APPEND)
		msg(">>'\n");
	if (token->type	== HEREDOC)
		msg("<<'\n");
	g_error = 1;
}
