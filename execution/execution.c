/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/31 04:48:22 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int is_bubul(char *src)
{
	if (ft_strcmp(src, "export") == 0 || ft_strcmp(src, "echo") == 0 || ft_strcmp(src, "cd") == 0 || ft_strcmp(src, "pwd") == 0 || ft_strcmp(src, "unset") == 0 || ft_strcmp(src, "env") == 0 || ft_strcmp(src, "exit") == 0)
		return (0);
	return (1);
}

int check_cmd(char *src, char *env, t_section *section)
{
	char **tmp;
	int i;

	i = 0;
	tmp = ft_split(env, ':');
	if (is_bubul(src) == 0)
		return (SUCCESS);
	while (tmp[i])
	{
		// printf("PATH = %s\t || %s\n", tmp[i], section->abs_path);
		if (ft_strcat_token(tmp[i], src, section) != 0)
			return (ERROR);
		if (access(section->abs_path, F_OK) != -1)
		{
			if (access(section->abs_path, X_OK) != -1)
				return (SUCCESS);
		}
		i++;
	}
	// printf("val abs = %s\n", section->abs_path);
	return (SUCCESS);
}

char *ft_get_env(t_env **env, char *str)
{
	char *res;
	t_env *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = *env;
	// printf("dans get env\n");
	while (tmp && ft_strcmp(tmp->name, str) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	res = ft_calloc((ft_strlen(tmp->name) + ft_strlen(tmp->content) + 2), sizeof(char));
	if (!res)
		return (NULL); // FREE ALLLLLLL
	while (tmp->name[j])
		res[i] = tmp->name[j++];
	j = 0;
	res[i] = '=';
	while (tmp->content[j])
		res[i++] = tmp->content[j++];
	return (res);
}

void	find_cmd(t_section *section)
{
	char *path;

	path = ft_get_env(section->env, "PATH");
	if (!path)
		return ;
	while (section)
	{
		if (section->cmd)
			check_cmd(section->cmd, path, section);
		section = section->next;
	}
}

void back_to_home(int *pid, int ret)
{
	int i;
	int status;
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

void end_of_exec(int *pid, int x, int y)
{
	free(pid);
	convert_file(x, y);
	close(x);
	close(y);
}

int master_exec(t_section *section)
{
	pid_t *pid;
	int j[2];
	int ret;

	if (!section->cmd)
		return (0);
	ret = 0;
	pid = calloc(ft_lstsize_section(section), sizeof(int));
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

void print_section(t_section *section)
{
	while (section)
	{
		// printf("%s\n", section->cmd);
		// printf("1\n");
		// printf("%s\n", section->abs_path);
		// printf("2\n");
		// printf("%s\n", section->option);
		// printf("3\n");
		// printf("%d\t%d\n", section->fd[0], section->fd[1]);
		// printf("4\n");
		// printf("%d\t%d\n", section->pipe[0], section->pipe[1]);
		// printf("%d\n", section->deep);
		cmd_env(section->env);
		print_token(section->token);
		section = section->next;
	}
}

int execution(t_token *token, t_env **env)
{
	t_section *list_section;
	t_token	*token_tmp;

	token_tmp = token;
	list_section = NULL;
	init_section(token_tmp, &list_section, env);
	find_cmd(list_section);
	// printf("section->cmd = %s\n", list_section->cmd);
	 // scan des differents token et verification de la validation des commandes
	// 	return (ERROR);						// free la structure
	// printf("valeur de cmd = %s \t||\t valeur de absPath = %s \t|| \t valeur des option = %s\n", list_section.cmd, list_section.abs_path, list_section.option);
	// printf("avant\n");
	if (master_exec(list_section) == -1)
		return (ERROR);
	return (SUCCESS);
}
