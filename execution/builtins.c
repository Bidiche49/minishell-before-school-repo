/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:38:25 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/02 09:46:12 by ntardy           ###   ########.fr       */
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
