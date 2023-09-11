/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:33:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/11 18:32:30 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	copy_var_env(char *dest, char *str, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (str[i + 1] == '?')
		{
			dest[i] = '0';
			return (2);
		}
		if ((str[i + 1] == '\0' || str[i + 1] == ' '
				|| str[i + 1] == '$' || !is_alnum_und(str[i + 1])))
			return (0);
		if (is_in_env(str, env) == 1)
		{
			while (env->content[i])
			{
				dest[i] = env->content[i];
				i++;
			}
			return (i);
		}
		env = env->next;
	}
	return (i);
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
			if (str[i] && str[i] == '$' && str[i + 1] != '$'
				&& (!is_alnum_und(str[i + 1])))
			{
				d_quotes[j++] = '$';
				i++;
			}
		}
		if (str[i] && str[i] != '$')
			d_quotes[j++] = str[i++];
	}
}

char	*dup_dquotes(int len_tot, char *str, t_env *env)
{
	char	*d_quotes;

	d_quotes = ft_calloc(len_tot, sizeof(char));
	if (d_quotes == NULL)
		return (malloc_error(), NULL);
	fill_dquote(str, env, d_quotes);
	if (str)
		free(str);
	return (d_quotes);
}

int	expand_d_quotes(t_token **list_token, t_env *env)
{
	t_token	*tmp;
	int		len_tot;

	tmp = *list_token;
	while (tmp)
	{
		if (is_an_exp_dquotes(tmp))
		{
			len_tot = calc_len_tot(tmp->str, env);
			if (len_tot == 1)
			{
				if (tmp->str)
					free(tmp->str);
				tmp->str = NULL;
			}
			else
			{
				tmp->str = dup_dquotes(len_tot, tmp->str, env);
				tmp->type = WORD;
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
