/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:33:56 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 22:34:08 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_word(t_token **token, t_env **env)
{
	t_env	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		if (special_case_expand(token) == 0)
			return (SUCCESS);
		else if (is_in_env((*token)->str, tmp_env) == 1)
		{
			free((*token)->str);
			(*token)->str = ft_strdup(tmp_env->content);
			if (!(*token)->str)
				return (g_error = MALL_KO, msg(ERR_MALLOC_KO), ERROR);
			return (SUCCESS);
		}
		tmp_env = tmp_env->next;
	}
	free((*token)->str);
	(*token)->str = NULL;
	return (SUCCESS);
}

int	expand_to_token(t_token **list_token)
{
	t_token	*tmp;

	tmp = *list_token;
	while (tmp)
	{
		if (tmp->next && tmp->type == WORD && tmp->next->type == WORD)
		{
			tmp->str = ft_strcat_dup(tmp->str, tmp->next->str);
			if (tmp->str == NULL)
				return (g_error = MALL_KO, msg(ERR_MALLOC_KO), ERROR);
			del_next_token(&tmp);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
