/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/15 17:50:38 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	check_cmd(char *src, char *env, t_section *section)
{
	char	**tmp;
	int	i;
	
	i = 0;
	tmp = ft_split(env, ':');
	while (tmp[i])
	{
		if (ft_strcat_token(tmp[i], src, section) != 0)
					return (ERROR);
		if (access(section->abs_path, F_OK) != -1)
		{
			if (access(section->abs_path, X_OK) != -1)
			{
				if (ft_strcpy_token(src, section) != 0)
					return (ERROR);
				return (SUCCESS);
			}
		}
		i++;
	}
	return (SUCCESS);
}

void	find_cmd(t_token *token, t_section *section)
{
	char	*env;
	
	env = getenv("PATH");
	if (token->type == WORD) 
	{
		if (check_cmd(token->str, env, section) != 0)
			section->cmd = NULL;
	}
	while (token)
	{
		if (token->type == PIPE)
			if (token->next->type == WORD)
				if (check_cmd(token->next->str, env, section) != 0)
					section->cmd = NULL;
		token = token->next;
	}
}			

int	gathering(t_token *token, t_section *section)
{
	while (token && ((is_redir(token->type) == 1) || token->type == PIPE))
	{
		if (token->type == SEPARATOR) 
			add_space(section);
		else if (token->type == WORD)
		{
			if (ft_strcat_exec_sec(section, token->str) != 0)
				return (ERROR);
		}
		else if (token->type == S_QUOTES)
		{
			if (ft_strcat_exec_sec_s(section, token->str) != 0)
				return (ERROR);
		}
		else if (token->type == D_QUOTES)
		{
			if (ft_strcat_exec_sec_d(section, token->str) != 0)
				return (ERROR);
		}
		token = token->next;
	}
	return (SUCCESS);
}

int	is_clear(t_token *token, t_section *section)
{
	find_cmd(token, section);
	while (section)
	{
		if (is_redir(token->type) == 1 || token->type == PIPE)
			section = section->next;
		if (section->cmd != NULL)
		{
			if (gathering(token, section) != 0)
				return (ERROR);
		}
		section = section->next;
	}
	return (SUCCESS);
}

int	exec_exe_simple(t_section *section, int pid)
{
	if (pid == 0 && execve(section->abs_path, ft_split(section->option, ' '), NULL) == -1)
		return (perror(section->abs_path), 1);
	return (0);
}

int	exec_all(t_section *section, int pid)
{
	
}

int	execution(t_token *token)
{
	t_section	list_section;
	int pid;
	
	pid = fork();
	init_list_section(token, &list_section);
	if (is_clear(token, &list_section) != 0) // scan des differents token et verification de la validation des commandes
		return (ERROR); // free la structure
	if (is_operator_exec(token) == 0 && exec_exe_simple(&list_section, pid) != 0)
		return (ERROR);
	// if (is_operator_exec(token) == 1 && exec_all(&list_section, pid))
	

	
	return (SUCCESS);
}
