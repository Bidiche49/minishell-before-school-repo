/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:50:01 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 21:33:07 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

t_env	*create_node(char *name, char *content)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (tracked_free(new), NULL);
	if (content)
	{
		new->content = ft_strdup(content);
		if (!new->content)
			return (free_new_env(new), NULL);
	}
	else
		new->content = NULL;
	new->next = NULL;
	return (new);
}

void	insert_sorted(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL || (new && ft_strcmp(new->name, (*env)->name) < 0))
	{
		new->next = *env;
		*env = new;
	}
	else
	{
		tmp = *env;
		while (tmp->next != NULL && ft_strcmp(new->name, tmp->next->name) > 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

t_env	*copy_and_sort_env(t_env *env)
{
	t_env	*sorted_env;
	t_env	*tmp;
	t_env	*new;

	tmp = env;
	new = NULL;
	sorted_env = NULL;
	while (tmp != NULL)
	{
		new = create_node(tmp->name, tmp->content);
		if (!new)
			return (NULL);
		insert_sorted(&sorted_env, new);
		tmp = tmp->next;
	}
	return (sorted_env);
}
