/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:00 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 08:52:09 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	error_redir(char *str, int referal)
{
	msg("minishell: ");
	msg(str);
	if (errno == 13)
		msg(ERR_PERM_DENIED);
	else
		msg(ERR_NO_FILE);
	g_error = 1;
	if (referal)
	{
		rl_clear_history();
		garbage_collect();
		exit(g_error);
	}
	else
		return (ERROR);
}
