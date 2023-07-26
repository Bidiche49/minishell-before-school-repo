/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:28:36 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/23 15:40:05 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	write(2, "exit\n", 7);
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		write(2, "minishell: exit: too many arguments\n", 37);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		write(2, "minishell: exit: \n", 19);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
}