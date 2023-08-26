/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 03:08:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/26 15:55:53 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	search_env(t_token **token, t_env **env)
{
	int	i;
	t_env	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		i = 0;
		while(tmp_env->name && (*token)->str && tmp_env->name[i] && (*token)->str[i + 1])
		{
			if (tmp_env->name[i] == (*token)->str[i + 1])
				i++;
			else
				break ;
		}
		if (tmp_env->name[i] == '\0' && (*token)->str[i + 1] == '\0')
		{
			free((*token)->str);
			(*token)->str = ft_strdup(tmp_env->content);
			if (!(*token)->str)
				return (write(0, ERR_MALLOC_KO, ft_strlen(ERR_MALLOC_KO)), ERROR);
			return (SUCCESS);
		}
		tmp_env = tmp_env->next;
	}
	free((*token)->str);
	(*token)->str = NULL;
	return (SUCCESS);
}

int	expand(t_token **list_token, t_env **env)
{
	t_token	*tmp;

	tmp = *list_token;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str[0] == '$')
			if (search_env(&tmp, env) == ERROR)
				return (free_all(list_token, env), ERROR); // NE PAS OUBLIER DE TOUT FREEEEEE----------------------------		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
