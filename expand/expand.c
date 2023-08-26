/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 03:08:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/26 17:08:49 by ntardy           ###   ########.fr       */
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

int	isexpand_ok(t_token *list_token)
{
	while (list_token)
	{
		if (list_token->next && list_token->type == WORD && list_token->next->type == WORD)
			return (ERROR);
		list_token = list_token->next;
	}
	return (SUCCESS);
}

void	del_next_token(t_token **token)
{
	t_token	*tmp;

	if (!(*token)->next)
		return ;
	tmp = (*token)->next->next;
	if ((*token)->next->str)
		free((*token)->next->str);
	free((*token)->next);
	(*token)->next = tmp;
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
				return (write(0, ERR_MALLOC_KO, ft_strlen(ERR_MALLOC_KO)), ERROR);
			del_next_token(&tmp);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	expand(t_token **list_token, t_env **env)
{
	t_token	*tmp;
	// int		expand_ok;

	tmp = *list_token;
	printf("enter expand\n");
	// expand_ok = 0;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str[0] == '$')
			if (search_env(&tmp, env) == ERROR)
				return (free_all(list_token, env), ERROR); // NE PAS OUBLIER DE TOUT FREE----------------------------		}
		tmp = tmp->next;
	}
	while (isexpand_ok(*list_token) == ERROR)
		if (expand_to_token(list_token) == ERROR)
			return (free_all(list_token, env), ERROR);
	return (SUCCESS);
}
