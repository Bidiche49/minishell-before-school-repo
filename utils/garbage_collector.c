/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:42:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/13 06:48:40 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_garbage	**get_garbage(void)
{
	static t_garbage	*garbage = NULL;
	return (&garbage);
}

void tracked_free(void *ptr)
{
	t_garbage **garbages;
	t_garbage *current;
	t_garbage *prev ;

	if (!ptr)
		return ;
	garbages = get_garbage();
	current = *garbages;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				(*garbages) = current->next;
			free(current->ptr);
			current->ptr = NULL;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}

}

void garbage_collect()
{
	t_garbage *current;
	t_garbage *tmp;

	current = *get_garbage();
	while (current) {
		tmp = current;
		current = current->next;
		free(tmp->ptr);
		free(tmp);
	}
}
