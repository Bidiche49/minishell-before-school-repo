/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:33:56 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 17:40:44 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_word(t_token **token, t_env **env)
{
	t_env	*tmp_env;

	tmp_env = *env;
	if (special_case_expand(token) == SUCCESS)
		return (SUCCESS);
	while (tmp_env)
	{
		if (is_in_env((*token)->str, tmp_env) == 1)
		{
			tracked_free((*token)->str);
			(*token)->str = ft_strdup(tmp_env->content);
			if (!(*token)->str)
				return (ERROR);
			return (SUCCESS);
		}
		tmp_env = tmp_env->next;
	}
	tracked_free((*token)->str);
	(*token)->str = NULL;
	return (SUCCESS);
}

int	expand_to_token(t_token **list_token, t_env **env)
{
	t_token	*tmp;

	tmp = *list_token;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str && tmp->str[0] == '$'
			&& tmp->str[1])
			if (expand_word(&tmp, env) == ERROR)
				return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
