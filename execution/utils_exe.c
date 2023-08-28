/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:40:19 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/07 18:51:01 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	ft_lstsize(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
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


int	cmp_operator(t_token *token)
{
	int	i;

	i = 0;
	while (token == NULL)
	{
		if (is_redir(token->type) == 1 || token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

t_section *ft_newsection()
{
	t_section *new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->cmd = NULL;
	new->option = NULL;
	new->next = NULL;
	new->abs_path = NULL;
	new->next = NULL;
	return (new);
}

int ft_lstadd_back_exec(t_section **lst, t_section *new)
{
	t_section *actu;

	if (new == NULL)
		return (1);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	actu = *lst;
	while (actu->next != NULL)
		actu = actu->next;
	actu->next = new;
	return (0);
}

void	init_list_section(t_token *token, t_section *section)
{
	int	nb_pipe;

	nb_pipe = cmp_operator(token); // compte le nombre de mots
	if (nb_pipe == 0)
	{
		section->cmd = NULL;
		section->option = NULL;
		section->next = NULL;
		section->abs_path = NULL;
		section->next = NULL;
	}
	while (nb_pipe > 0)
	{
		ft_lstadd_back_exec(&section, ft_newsection());
		section = section->next;
		nb_pipe--;
	}
}