/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:14 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 20:32:19 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_matrice(char **matrice)
{
	int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
		tracked_free(matrice[i++]);
	tracked_free(matrice);
	matrice = NULL;
}

void	free_list_token(t_token **lst_token)
{
	t_token	*tmp;

	tmp = *lst_token;
	if ((*lst_token) && !(*lst_token)->next)
		tracked_free((*lst_token));
	while ((*lst_token))
	{
		tmp = (*lst_token)->next;
		if ((*lst_token)->str)
			tracked_free((*lst_token)->str);
		tracked_free((*lst_token));
		(*lst_token) = tmp;
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while ((*env))
	{
		tmp = (*env)->next;
		if ((*env)->name)
			tracked_free((*env)->name);
		if ((*env)->content)
			tracked_free((*env)->content);
		tracked_free((*env));
		(*env) = tmp;
	}
}

void	free_all(t_token **lst_token, t_env **env)
{
	if ((*lst_token))
		free_list_token(lst_token);
	if (env)
		free_env(env);
}
