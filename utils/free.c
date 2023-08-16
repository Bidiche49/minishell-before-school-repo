/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:14 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/07 16:53:05 by audrye           ###   ########.fr       */
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
void free_all(t_token *lst_token)
{
	// t_token	*tmp;

	printf("test\n");
	if (!lst_token)
		return;

	free(lst_token);
	printf("fin free\n");
}
