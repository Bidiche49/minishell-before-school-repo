/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:33:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 02:34:45 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	calc_len_tot(char *str, t_env *env)
{
	int	i;
	int	len_tot;

	i = 0;
	len_tot = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			len_tot += (count_len_var_content(str + i, env)
					- count_len_var_name(str + i));
		i++;
	}
	len_tot += i + 1;
	return (len_tot);
}

int	is_an_exp_dquotes(t_token *list_token)
{
	int	i;

	i = 0;
	if (list_token->type == D_QUOTES)
	{
		while (list_token->str && list_token->str[i])
		{
			if (list_token->str[i + 1] && list_token->str[i] == '$'
				&& is_alnum_und(list_token->str[i + 1]))
				return (1);
			i++;
		}
	}
	return (0);
}

void	fill_dquote(char *str, t_env *env, char *d_quotes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			j += copy_var_env(d_quotes + j, str + i, env);
			i += count_len_var_name(str + i);
			if (str[i] && str[i] == '$' && (!str[i + 1] || str[i + 1] == ' '))
			{
				d_quotes[j++] = '$';
				i++;
			}
		}
		if (str[i] && str[i] != '$')
		{
			d_quotes[j++] = str[i++];
		}
	}
	d_quotes[j] = '\0';
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
	if (str[i + 1] == ' ' || !str[i + 1])
		return (0);
	if (is_num(str[i + 1]) == 1 || str[i + 1] == '?'
		|| str[i + 1] == '$' || str[i + 1] == '\\')
		return (2);
	while (str && str[i + 1] && is_alnum_und(str[i + 1]))
		i++;
	printf("len_VARNAME %s = %d\n", str + i + 1, i);
	return (i + 1);
}
