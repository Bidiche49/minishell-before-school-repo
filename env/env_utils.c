/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:06:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 03:17:17 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

	i = -1;
	if (env_var[i + 2] && !is_alnum_und(env_var[i + 2]))
		return (0);
	while (env->name && env_var && env->name[++i])
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

int	atoi_shlvl(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "SHLVL"))
			return (ft_atoi(tmp->content));
		tmp = tmp->next;
	}
	return (1);
}

int	increment_shlvl(t_env **env)
{
	char	*shlvl_str;

	shlvl_str = ft_strjoin("SHLVL=", ft_itoa(atoi_shlvl(env) + 1));
	if (shlvl_str == NULL)
		return (0);
	return (mod_exist_var(env, shlvl_str));
}
