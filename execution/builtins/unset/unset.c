/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:45:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 15:04:59 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void	cmd_unset(t_section *sec)
{
	t_token	*tok;

	g_error = 0;
	tok = sec->token;
	if (sec->deep > 1)
		return ;
	if (tok && tok->next && tok->next->next && tok->next->next->type == WORD)
		return (del_var_env(sec->env, tok->next->next));
	return ;
}
