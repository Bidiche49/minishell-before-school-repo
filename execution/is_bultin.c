/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bultin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:35:14 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 00:42:21 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_bultin(t_section *section)
{
	if (ft_strcmp(section->cmd, "echo") == 0)
		ft_echo(section);
	else if (ft_strcmp(section->cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "env") == 0)
		return (cmd_env(section->env));
	else if (ft_strcmp(section->cmd, "exit") == 0)
		return (0);
	else
		return (1);
	if (section->next)
		return (2);
	return (0);
}

int util_dup2(t_section *section, int x, int y)
{
	int i;

	convert_file(section->fd[0], section->fd[1]);
	i = is_bultin(section);
	convert_file(x, y);
	return (i);
}