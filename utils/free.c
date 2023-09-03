/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:14 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/02 00:51:49 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_list_token(t_token **lst_token)
{
	t_token *tmp;

	tmp = *lst_token;
	while ((*lst_token))
	{
		tmp = (*lst_token)->next;
		// printf("token->str =%s\n", (*lst_token)->str);
		if ((*lst_token)->str)
			free((*lst_token)->str);
		free((*lst_token));
		(*lst_token) = tmp;
	}
}

void free_env(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while ((*env))
	{
		tmp = (*env)->next;
		if ((*env)->name)
			free((*env)->name);
		if ((*env)->content)
			free((*env)->content);
		free((*env));
		(*env) = tmp;
	}
}

void free_all(t_token **lst_token, t_env **env)
{
	// t_token	*tmp;

	if (lst_token)
		free_list_token(lst_token);
	if (env)
		free_env(env);
	printf("fin free\n");
}

void free_env_char(char **env)
{
	int i;

	i = 0;
	while (env)
		free(env[i++]);
	free(env);
}