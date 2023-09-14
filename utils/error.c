/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 03:40:08 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 20:47:44 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
