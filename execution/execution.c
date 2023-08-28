/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/28 04:56:56 by audrye           ###   ########.fr       */
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

void	back_to_home(int *pid, int ret)
{
	int	i;
	int	status;
	int error;

	i = 0;
	while (i != ret)
	{
		if (waitpid(-1, &status, WUNTRACED) == pid[ret - 1])
		{
			if (status == 2)
				error = 130;
			else if (status > 256)
				error = status / 256;
			else
				error = status;
		}
		i++;
	}
	if (error == 130 || error == 131)
		write(1, "\n", 1);
}
void	end_of_exit(int *pid, int x, int y)
{
	free(pid);
	convert_file(x, y);
	close(x);
	close(y);
}
int	master_exec(t_section *section)
{
	int		*pid;
	int		j[2];
	int		ret;
	
	pid = malloc(sizeof(int) * ft_lstsize_section(section));
	if (!pid)
		return (0);
	j[0] = dup(0);
	j[1] = dup(1);
	if (exec_pipe(section, j[1], j[0]) == -1)
		return (close(j[1]), close(j[0]), -1);
	signal(SIGINT, SIG_IGN);
	ret = fork_using(section, pid, j, NULL);
	if (ret == -1)
		return (close(j[0]), close(j[1]), free(pid), -1);
	if (pid[0] != -1)
		back_to_home(pid, ret);
	return (end_of_exec(pid, j[0], j[1]), 0);
}

int	execution(t_token *token, t_env **env)
{
	t_section	list_section;
	t_file		list_file;
	
	init_list_section(token, &list_section, (*env));
	init_file(token, &list_file);
	if (is_clear(token, &list_section) != 0) // scan des differents token et verification de la validation des commandes
		return (ERROR); // free la structure
	if (is_operator_exec(token) == 0 && master_exec(&list_section) != 0)
		return (ERROR);
	// if (is_operator_exec(token) == 1 && exec_all(&list_section, pid))
	return (SUCCESS);
}
