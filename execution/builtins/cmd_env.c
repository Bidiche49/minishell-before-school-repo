/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:17:52 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 08:07:44 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_env(t_env **env)
{
	t_env *tmp;
	printf("entree dans la command: cmd_env !\n");
	tmp = *env;
	printf("1\n");
	while(tmp)
	{
		printf("while1\n");
		if (tmp->name && tmp->content)
		{
			write(1, tmp->name, ft_strlen(tmp->name));
			write(1, "=", 1);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
			// printf("%s=%s\"\n", tmp->name, tmp->content);
			// printf("in\n");
		}
		printf("while2\n");
		tmp = tmp->next;
	}
	printf("fin cmd_env\n");
	return (0/*---------------------A VOIR----------------------------------*/);
}
