/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 03:40:08 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 22:03:59 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	msg(char *str)
{
	int	i;

	i = 0;
	i = ft_strlen(str);
	write(STDERR_FILENO, str, i);
}

void	malloc_error(void)
{
	g_error = MALL_KO;
	msg(ERR_MALLOC_KO);
	rl_clear_history();
	garbage_collect();
	exit(MALL_KO);
}

void	cmd_not_found(char *cmd)
{
	g_error = CMD_KO;
	msg("minishell: ");
	msg(cmd);
	msg(ERR_CMD_NOT_FOUND);
}

void	error_export(char *line)
{
	g_error = 1;
	msg("export `");
	msg(line);
	msg("' : not a valid identifier\n");
}

int	error_redir(char *str, int referal)
{
	msg("minishell: ");
	msg(str);
	if (errno == 13)
	{
		msg(ERR_PERM_DENIED);
		g_error = 126;
	}
	else
	{
		msg(ERR_NO_FILE);
		g_error = 127;
	}
	if (referal)
	{
		rl_clear_history();
		garbage_collect();
		exit(g_error);
	}
	else
		return (ERROR);
}

// void	err_end_token(int type)
// {
// 	msg(ERR_END_TOKEN);
// 	if (type == -1)
// 		msg("newline'\n");
// 	else if (type == PIPE)
// 		msg("|'\n");
// 	else if (type == IN)
// 		msg("<'\n");
// 	else if (type == OUT)
// 		msg(">'\n");
// 	else if (type == APPEND)
// 		msg(">>'\n");
// 	else if (type == HEREDOC)
// 		msg("<<'\n");
// 	g_error = 1;
// }
