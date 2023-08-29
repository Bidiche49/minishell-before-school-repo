/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:17:52 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 06:04:31 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_env(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if (tmp->name && tmp->content)
		{
			write(1, tmp->name, ft_strlen(tmp->name));
			write(1, "=", 1);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (g_error = 0, 1);
}
