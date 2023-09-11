/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:38:25 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/10 16:45:37 by audrye           ###   ########.fr       */
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
		ft_echo(sec);
	if (!ft_strcmp(sec->cmd, "unset"))
		return (cmd_unset(sec), 0);//GERER LA SORTIE !!!!!!!!!!!!!!!!!
	if (!ft_strcmp(sec->cmd, "pwd"))
		return (0);
	if (!ft_strcmp(sec->cmd, "cd"))
		return (0);
	if (!ft_strcmp(sec->cmd, "export"))
		return (cmd_export(sec), 0);//GERER LA SORTIE !!!!!!!!!!!!!!!!!
	if (!ft_strcmp(sec->cmd, "env"))
		return (cmd_env(sec->env), 0);//GERER LA SORTIE !!!!!!!!!!!!!!!!!
	if (!ft_strcmp(sec->cmd, "exit"))
		return (0);
	return (1);
}
