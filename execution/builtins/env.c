/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:29:13 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/23 15:19:35 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl(env->value);
	return (0);
}
