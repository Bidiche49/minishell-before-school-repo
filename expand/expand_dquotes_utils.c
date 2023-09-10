/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:33:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/02 01:34:24 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	count_dble_d(char *str)
{
	int	i;
	int	nb_dble_d;

	i = 0;
	nb_dble_d = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '$')
		{
			i += 2;
			nb_dble_d++;
		}
		i++;
	}
	return (nb_dble_d * 2);
}

int	calc_len_tot(char *str, t_env *env)
{
	int	i;
	int	len_tot;

	i = 0;
	len_tot = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && is_alnum_und(str[i + 1]))
			len_tot += (count_len_var_content(str + i, env)
					- count_len_var_name(str + i));
		i++;
	}
	len_tot += i + 1 - count_dble_d(str);
	return (len_tot);
}

int	count_len_var_content(char *str, t_env *env)
{
	while (env)
	{
		if (is_in_env(str, env) == 1)
			return (ft_strlen(env->content));
		env = env->next;
	}
	return (0);
}

int	count_len_var_name(char *str)
{
	int	i;

	i = 0;
	if (is_num(str[i + 1]) == 1 || str[i + 1] == '?'
		|| str[i + 1] == '$')
		return (2);
	if (!is_alnum_und(str[i + 1]))
		return (0);
	while (str && str[i + 1] && is_alnum_und(str[i + 1]))
		i++;
	return (i + 1);
}
