/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/29 00:06:31 by audrye           ###   ########.fr       */
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

char	*ft_get_path(t_env	**env)
{
	char	*path;
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = *env;
	while (tmp && ft_strcmp(tmp->name, "PATH") != 0)
		tmp=tmp->next;
	path = malloc(sizeof(char) * (ft_strlen(tmp->name) + ft_strlen(tmp->content) + 2));
	if (!path)
		return (NULL); //FREE ALLLLLLL
	while (tmp->name[j])
		path[i] = tmp->name[j++];
	j = 0;
	path[i] = '=';
	while (tmp->content[j])
		path[i++] = tmp->content[j++];
	path[i] = '\0';
	return (path);
}

void	find_cmd(t_token *token, t_section *section)
{
	char	*path;
	
	// cmd_env(section->env);
	path = getenv("PATH");
	// path = ft_get_path(section->env);
	if (!path)
		return ;
	// cmd_env(section->env);
	if (token->type == WORD)
	{
		if (check_cmd(token->str, path, section) != 0)
			section->cmd = NULL;
	}
	while (token)
	{
		if (token->type == PIPE)
			if (token->next->type == WORD)
				if (check_cmd(token->next->str, path, section) != 0)
					section->cmd = NULL;
		token = token->next;
	}
	printf("dans find cmd\n");
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
void	end_of_exec(int *pid, int x, int y)
{
	free(pid);
	convert_file(x, y);
	close(x);
	close(y);
}
int	master_exec(t_section *section)
{
	pid_t		*pid;
	int		j[2];
	int		ret;
	
	if (!section->cmd)
		return (0);
	ret = 0;
	pid = malloc(sizeof(int) * ft_lstsize_section(section));
	if (!pid)
		return (0);
	pid[0] = -1;
	j[1] = dup(1);
	j[0] = dup(0);
	if (exec_pipe(section, j[1], j[0]) == -1)
		return (close(j[1]), close(j[0]), -1);
	signal(SIGINT, SIG_IGN);
	ret = fork_using(section, pid, j);
	if (ret == -1)
		return (close(j[1]), close(j[0]), free(pid), -1);
	if (pid[0] != -1)
		back_to_home(pid, ret);
	return (end_of_exec(pid, j[0], j[1]), 1);
}

int	execution(t_token *token, t_env **env)
{
	t_section	list_section;
	// t_file		list_file;
	
	init_list_section(token, &list_section, (*env));
	// init_file(token, &list_file);
	// cmd_env(*list_section.env);
	printf("avant master_exec\n");
	if (is_clear(token, &list_section) != 0) // scan des differents token et verification de la validation des commandes
		return (ERROR); // free la structure
	if (master_exec(&list_section) == -1)
		return (ERROR);
	// if (is_operator_exec(token) == 1 && exec_all(&list_section, pid))
	return (SUCCESS);
}
