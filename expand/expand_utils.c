/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:16:41 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/27 01:22:41 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

int	is_alnum_und(char c)
{
	if (is_num(c) == 1 || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	is_in_env(char *env_var, t_env *env)
{
	int	i;

	i = 0;
	while(env->name && env_var && env->name[i])
	{
		if (env->name[i] == env_var[i + 1])
		{
			if (is_num(env_var[i + 1]) == 1)
			{
				if (env->name[i + 1] == '\0')
					return (1);
				else
					break ;
			}
			i++;
		}
		else
			break ;
	}
	if (env->name[i] == '\0' && (env_var[i + 1] == '\0' || env_var[i + 1] == ' '))
	{
		printf("est dans l'env\n");
		return (1);
	}
	return (0);
}
