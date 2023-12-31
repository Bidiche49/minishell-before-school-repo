/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:38:25 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 15:15:25 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(t_section *sec)
{
	if (!ft_strcmp(sec->cmd, "echo") || !ft_strcmp(sec->cmd, "unset"))
		return (1);
	if (!ft_strcmp(sec->cmd, "pwd") || !ft_strcmp(sec->cmd, "cd"))
		return (1);
	if (!ft_strcmp(sec->cmd, "export") || !ft_strcmp(sec->cmd, "env"))
		return (1);
	if (!ft_strcmp(sec->cmd, "exit"))
		return (1); // return EXIT directement !!
	return (0);
}

int	exec_builtins(t_section *sec)
{
	if (!ft_strcmp(sec->cmd, "echo"))
		return (ft_echo(sec->option), 0);
	if (!ft_strcmp(sec->cmd, "unset"))
		return (g_error = 0, cmd_unset(sec), SUCCESS);//GERER LA SORTIE !!!!!!!!!!!!!!!!!
	if (!ft_strcmp(sec->cmd, "pwd"))
		return (0);
	if (!ft_strcmp(sec->cmd, "cd"))
		return (0);
	if (!ft_strcmp(sec->cmd, "export"))
		return (cmd_export(sec));//GERER LA SORTIE !!!!!!!!!!!!!!!!!
	if (!ft_strcmp(sec->cmd, "env"))
		return (cmd_env(sec->env));//GERER LA SORTIE !!!!!!!!!!!!!!!!!
	if (!ft_strcmp(sec->cmd, "exit"))
		return (cmd_exit(sec->option), 0);
	return (1);
}
