/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:06:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 05:01:20 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	ft_strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int	is_in_env(char *env_var, t_env *env)
{
	int	i;

	i = 0;
	if (env_var[i + 1] && !is_alnum_und(env_var[i + 1]))
		return (0);
	while (env->name && env_var && env->name[i])
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
	if (env->name[i] == '\0' && (env_var[i + 1] == '\0'
			|| env_var[i + 1] == ' ' || env_var[i + 1] == '$'
			|| env_var[i + 1] == '\\'))
		return (1);
	return (0);
}
