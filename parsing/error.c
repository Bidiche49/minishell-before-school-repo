/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:00 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 22:32:32 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
