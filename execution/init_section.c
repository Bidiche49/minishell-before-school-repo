/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_section.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:40:19 by augustindry       #+#    #+#             */
/*   Updated: 2023/09/12 14:40:35 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void free_section(t_section *section)
{
	if (!section)
		return;
	if (section->cmd)
		free(section->cmd);
	if (section->abs_path)
		free(section->abs_path);
	if (section->option)
		free(section->option);
	free(section);
	section = NULL;
}

int is_word(int type)
{
	if (type == WORD || type == S_QUOTES || type == D_QUOTES)
		return (1);
	return (0);
}

int is_redir(int type)
{
	if (type == IN || type == OUT || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int count_section(t_token *token)
{
	int i;

	i = 1;
	while (token)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

int strjoin_gathering(t_section **section, char *str)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strjoin((*section)->option, str);
	if (tmp == NULL)
		return (malloc_error(), ERROR);
	if ((*section)->option)
		free((*section)->option);
	(*section)->option = ft_strdup(tmp);
	free(tmp);
	if ((*section)->option == NULL)
		return (malloc_error(), ERROR);
	return (SUCCESS);
}

int gathering(t_token *token, t_section **section)
{
	t_token *tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == SEPARATOR)
		{
			while (tmp && (tmp->type == SEPARATOR || is_redir(tmp->type)))
				tmp = tmp->next;
			if (strjoin_gathering(section, " ") == ERROR)
				return (ERROR);
			if (!tmp || tmp->type == PIPE)
				break;
		}
		if (tmp->type == WORD || tmp->type == S_QUOTES || tmp->type == D_QUOTES)
		{
			if (strjoin_gathering(section, tmp->str) == ERROR)
				return (ERROR);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	init_base_section(t_token *token, t_env **env, t_section *new)
{
	new->cmd = NULL;
	new->option = NULL;
	new->token = token;
	new->env = env;
	new->deep = count_section(token);
	new->abs_path = NULL;
	new->pipe[0] = 0;
	new->pipe[1] = 0;
	new->fd[0] = 0;
	new->fd[1] = 0;
	new->next = NULL;
}

t_section *new_section(t_token *token, t_token *tmp_token, t_env **env)
{
	t_section *new;

	new = ft_calloc(1, sizeof(t_section));
	if (!new)
		return (malloc_error(), NULL);
	init_base_section(token, env, new);
	if (tmp_token->type == SEPARATOR)
		tmp_token = tmp_token->next;
	if (is_word(tmp_token->type))
	{
		new->cmd = ft_strdup(tmp_token->str);
		if (!new->cmd)
			return (free(new), malloc_error(), NULL);
	}
	if (gathering(tmp_token, &new) == ERROR)
		return (free(new), NULL);
	return (new);
}

int list_add_back_section(t_section **section, t_section *new)
{
	t_section *tmp;

	tmp = (*section);
	if (new == NULL)
		return (ERROR);
	if (*section == NULL)
		*section = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}

void free_list_section(t_section **section)
{
	t_section *current;
	t_section *next;

	current = *section;
	while (current)
	{
		next = current->next;
		free_section(current);
		current = next;
	}

	*section = NULL; // Mettre à NULL après avoir libéré tous les éléments
}


int init_section(t_token *token, t_section **section, t_env **env)
{
	t_token *tmp;
	int nb_section;

	tmp = token;
	nb_section = count_section(token);
	while (tmp && nb_section > 0)
	{
		if (list_add_back_section(section, new_section(token, tmp, env)) == ERROR)
			return (free_list_section(section), ERROR); // rajouter une fonction d'erreur pour les mallocs
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		nb_section--;
	}
	return (SUCCESS);
}
