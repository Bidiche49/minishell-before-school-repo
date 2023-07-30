/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/30 03:09:15 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	check_cmd(char *src, char env, t_token *token, t_section *section)
{
	char	**tmp;
	int	i;
	
	i = 0;
	tmp = ft_split(env, ':');
	while (tmp[i])
	{
		if (access(tmp[i], F_OK) != -1)
		{
			if (access(tmp[i], X_OK) != -1)
			{
				if (ft_strcat_token(tmp[i], src, section) != 0)
					return (ERROR);
				if (ft_strcpy_token(src, section) != 0)
					return (ERROR);
				return (SUCCES);
			}
		}
		i++;
	}
	return (SUCCES);
}

void	find_cmd(t_token *token, t_section *section)
{
	char	*env;
	
	env = getenv("PATH");
	if (token->type == WORD) 
	{
		if (check_cmd(token->type, env, token, section) != 0)
			section->cmd == NULL;
	}
	while (token)
	{
		if (token->type == PIPE)
			if (token->type == WORD)
				if (check_cmd(token->type, env, token, section) != 0)
					section->cmd == NULL;
		token = token->next;
	}
}

int	gathering(t_token *token, t_section *section)
{
	while (token->type != PIPE)
	{
		if (token->type == SEPARATOR)
			section->option = add_space(section->option);
		else if (token->type == WORD || token->type == OUT || token->type == IN
					|| token->type == HEREDOC || token->type == APPEND)
			if (ft_strcat_exec_sec(section, token->type) != 0)
				return (ERROR);
		else if (token->type == S_QUOTES)
			if (ft_strcat_exec_sec_s(section, token->type) != 0)
				return (ERROR);
		else if (token->type == D_QUOTES)
			if (ft_strcat_exec_sec_d(section, token->type) != 0)
				return (ERROR);
		token = token->next;
	}
	return (SUCCES);
}

int	is_clear(t_token *token, t_section *section) // si il ne faut pas faire execve la variable CMD sera initialiser a NULL
{
	find_cmd(token, section);
	while (section)
	{
		if (token->type == PIPE)
			section = section->next;
		if (section->cmd != NULL)
			if (gathering(token, section) != 0)
				return (ERROR);
	}
	return (SUCCES);
}

int	exec_exe(t_section *section)
{
	execve(section->abs_path, section->option, NULL);
}

int	execution(t_token *token)
{
	t_section	list_section;

	init_list_section(token, &list_section);
	if (is_clear(token, &list_section) != 0) // scan des differents token et verification de la validation des commandes
		return (ERROR); // free la structure
	if (exec_exe(&list_section) != 0)
		return (ERROR);
	return (SUCCES);
}
