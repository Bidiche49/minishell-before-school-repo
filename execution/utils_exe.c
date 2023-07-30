/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:40:19 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/30 01:37:20 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_lstsize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_section	*ft_lstlast(t_section *lst)
{	
	if (lst == NULL)
		return (NULL);
	while (lst->next)
			lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_section **lst, t_section *new)
{
	t_section	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

int	cmp_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

void	init_list_section(t_section *section, t_token *token)
{
	t_section *new;
	int	nb_pipe;

	nb_pipe = cmp_pipe(token); // compte le nombre de mots
	new->cmd = NULL;
	new->option = NULL;
	new->next = NULL;
	new->abs_path = NULL;
	while (nb_pipe >= 0)
	{
		ft_lstadd_back(&section, new);
		section = section->next;
		nb_pipe--;
	}
}