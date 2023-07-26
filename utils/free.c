/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:14 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/26 22:59:30 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list_token(t_token *lst_token)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp)
	{
		// print_token(lst_token); // Affiche les jetons (tokens) analysés à des fins de test.
		if (tmp->next == NULL)
		{
			if (tmp->str)
				free(tmp->str);
			tmp = NULL;
			tmp = lst_token;
		}
		tmp = tmp->next;
	}
}

void	free_all(t_token *lst_token)
{
	// t_token	*tmp;

	printf("test\n");
	if(!lst_token)
		return ;

	free(lst_token);
	printf("fin free\n");
}
