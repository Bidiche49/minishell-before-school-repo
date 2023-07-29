/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:44:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/29 01:17:05 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	is_sep_op(char c)
{
	if (c == '\0' || c == '|' || c == '<' || c == '>' || c == ' '|| c == '$' || c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_operator(t_token *token)
{
	if (token->type == IN || token->type == OUT || token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}
int	is_word_quote(t_token *token)
{
	if (token->type == WORD || token->type == D_QUOTES || token->type == S_QUOTES)
		return (1);
	return (0);
}
