/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:16:41 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 23:17:18 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	is_op(t_token *token)
{
	if (token->type == OUT || token->type == IN || token->type == HEREDOC
		|| token->type == APPEND || token->type == PIPE)
		return (1);
	return (0);
}

int	is_type_wq(t_token *token)
{
	if (token->type == WORD || token->type == S_QUOTES
		|| token->type == D_QUOTES)
		return (1);
	return (0);
}

int	cat_word(t_token *token)
{
	if (!token->str || (token->next && !token->next->str))
		return (SUCCESS);
	token->str = ft_strcat_dup(token->str, token->next->str);
	if (!token->str)
		return (ERROR);
	del_next_token(&token);
	return (SUCCESS);
}

int	is_sep_pipe(t_token *token)
{
	if (token->type == SEPARATOR || token->type == PIPE)
		return (1);
	return (0);
}
