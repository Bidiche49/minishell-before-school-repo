/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:16:41 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/27 22:35:55 by ntardy           ###   ########.fr       */
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
	if (env->name[i] == '\0' && (env_var[i + 1] == '\0' || env_var[i + 1] == ' ' || env_var[i + 1] == '$' || env_var[i + 1] == '\\'))
	{
		// printf("est dans l'env\n");
		return (1);
	}
	return (0);
}

int isexpand_ok(t_token *list_token)
{
	while (list_token)
	{
		// if (list_token->next && list_token->type == WORD && list_token->next->type == WORD)
		// 	return (ERROR);
		// else if (list_token->next && list_token->next->type == WORD && list_token->next->str == NULL)
		// 	return (ERROR);
		// else if (!list_token->next && list_token->type == SEPARATOR)
		// 	return (ERROR);
		// else if (list_token->next && list_token->type == SEPARATOR && list_token->next->type == SEPARATOR)
		// 	return (ERROR);
		if (is_an_exp_dquotes(list_token) == 1)
			return (ERROR);
		list_token = list_token->next;
	}
	return (SUCCESS);
}

void del_next_token(t_token **token)
{
	t_token *tmp;

	if (!(*token)->next)
		return;
	tmp = (*token)->next->next;
	if ((*token)->next->str)
		free((*token)->next->str);
	free((*token)->next);
	(*token)->next = tmp;
}

int is_an_exp_dquotes(t_token *list_token)
{
	int i;

	i = 0;
	if (list_token->type == D_QUOTES)
		while (list_token->str && list_token->str[i])
		{
			if (list_token->str[i + 1] && list_token->str[i] == '$' && list_token->str[i + 1] != ' ')
				return (1);
			i++;
		}
	return (0);
}
