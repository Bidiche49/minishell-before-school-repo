/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:17:52 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 22:13:31 by ntardy           ###   ########.fr       */
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
			printf(BOLD YELLOW "%s=" RESET, tmp->name);
			printf(CYAN "%s\n" RESET, tmp->content);
		}
		tmp = tmp->next;
	}
	return (g_error = 0, 1);
}
