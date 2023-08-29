/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:40:19 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/29 12:28:19 by audrye           ###   ########.fr       */
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

int	ft_lstsize_section(t_section *section)
{
	int	i;

	i = 0;
	while (section)
	{
		section = section->next;
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
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

t_section *ft_newsection(t_env **env)
{
	t_section *new;

	new = malloc(sizeof(t_section));
	if (new == NULL)
		return (NULL);
	new->cmd = NULL;
	new->option = NULL;
	new->abs_path = NULL;
	new->env = env;
	new->fd[1] = -2;
	new->fd[2] = -2;
	new->pipe[1] = -1;
	new->pipe[2] = -1;
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

void	set_section_one(t_section *section, t_token *token, t_env **env)
{
	section->cmd = NULL;
	section->option = NULL;
	section->abs_path = NULL;
	section->env = env;
	section->deep = 0;
	section->fd[1] = -2;
	section->fd[2] = -2;
	section->pipe[1] = -1;
	section->pipe[2] = -1;
	section->next = NULL;
	section->token = token;
	section->file = NULL;
}

void	init_list_section(t_token *token, t_section *section, t_env **env)
{
	int	nb_pipe;
	int	i;

	i = 0;
	nb_pipe = cmp_operator(token); // compte le nombre de mots
	if (nb_pipe == 0)
		set_section_one(section, token, env);
	while (nb_pipe > 0)
	{
		ft_lstadd_back_exec(&section, ft_newsection(env));
		section->deep = i++;
		section = section->next;
		nb_pipe--;
	}
}

t_file *ft_newsection_file(t_token *token)
{
	t_file *new;

	new = malloc(sizeof(t_file));
	if (new == NULL)
		return (NULL);
	new->name = calloc(ft_strlen(token->str), sizeof(t_file));
	new->name = token->str;
	new->type = token->type;
	new->next = NULL;
	return (new);
}

int ft_lstadd_back_exec_file(t_file **lst, t_file *new)
{
	t_file *actu;

	if (new == NULL)
		return (1);
	if (lst == NULL)
	{
		*lst = new;
		return (0);
	}
	actu = *lst;
	while (actu->next != NULL)
		actu = actu->next;
	printf("valeur de new->name = %s\n", new->name);
	actu->next = new;
	return (0);
}

int	is_separator(t_token *token)
{
	int i;
	
	i = 0;
	while (token)
	{
		if (token->type == SEPARATOR)
			i--;
		token = token->next;
		i++;
	}
	return (i);
}

void	init_file(t_token *token, t_file *file)
{
	int	i;

	i = is_separator(token);
	while (i > 0)
	{
		if (token->type != SEPARATOR)
			ft_lstadd_back_exec_file(&file, ft_newsection_file(token));
		token = token->next;
		i--;
	}
}