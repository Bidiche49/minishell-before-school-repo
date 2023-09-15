/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:12:20 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 21:55:18 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	err_cmd_path(char *cmd, char *err, int error)
{
	msg("minishell: ");
	msg(cmd);
	msg(err);
	g_error = error;
	rl_clear_history();
	garbage_collect();
	exit(g_error);
}

void	err_end_token(int type)
{
	msg(ERR_END_TOKEN);
	if (type == -1)
		msg("newline'\n");
	else if (type == PIPE)
		msg("|'\n");
	else if (type == IN)
		msg("<'\n");
	else if (type == OUT)
		msg(">'\n");
	else if (type == APPEND)
		msg(">>'\n");
	else if (type == HEREDOC)
		msg("<<'\n");
	g_error = 1;
}
