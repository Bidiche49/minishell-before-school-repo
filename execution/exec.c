/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:06:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/13 05:28:24 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_lstsize_env(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

int ft_lstsize_section(t_section *section)
{
	int i;

	i = 0;
	while (section)
	{
		section = section->next;
		i++;
	}
	return (i);
}

char *cpy_new_line(char *tmp, char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i++] = '=';
	while (s2[j])
	{
		tmp[i] = s2[j];
		i++;
		j++;
	}
	return (tmp);
}

char **convert_env(t_env **env)
{
	char **env_tmp;
	t_env *tmp;
	int i;
	int size;

	i = 0;
	tmp = *env;
	env_tmp = ft_calloc((ft_lstsize_env(*env) + 1), sizeof(char *));
	if (!env_tmp)
		return (NULL); // FREEEEEALLALALALALAL
	tmp = *env;
	while (tmp)
	{
		size = ft_strlen(tmp->name) + ft_strlen(tmp->content);
		env_tmp[i] = ft_calloc((size + 3), sizeof(char));
		if (!env_tmp[i])
			return (free_matrice(env_tmp), NULL); // FREE ALLLLLLL
		env_tmp[i] = cpy_new_line(env_tmp[i], tmp->name, tmp->content);
		i++;
		tmp = tmp->next;
	}
	return (env_tmp);
}

int openfiles(t_token *token)
{
	int fd;

	fd = -1;
	while (token && token->type != PIPE)
	{
		if (token->type == OUT || token->type == IN || token->type == APPEND)
		{
			if (token->type == OUT)
				fd = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (token->type == APPEND)
				fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (token->type == IN || token->type == HEREDOC)
				fd = open(token->str, O_RDONLY);
			if (fd == -1)
				exit(1);
			if (token->type == OUT || token->type == APPEND)
				dup2(fd, STDOUT_FILENO);
			else
				dup2(fd, STDIN_FILENO);
		}
		token = token->next;
	}
	return (fd);
}

void redirection(int *data, int last, t_section *section)
{
	t_token *token;
	int redir;

	token = section->token;
	redir = openfiles(token);
	if (redir >= 0)
		data[TMP_FD1] = redir;
	// close(redir);
	if (data[I] != 0)
	{
		dup2(data[PREV], STDIN_FILENO);
		close(data[PREV]);
	}
	if (data[I] != last)
		dup2(data[TMP_FD1], STDOUT_FILENO);
	close(data[TMP_FD0]);
	close(data[TMP_FD1]);
}

int exec(t_section *section, int *pid, int *data, char **arg, char **env)
{
	// close(pid[data[I]]);
	tracked_free(pid);
	find_path(section);
	redirection(data, section->deep - 1, section);
	arg = ft_split(section->option, ' ');
	if (!arg)
		return (malloc_error(), ERROR);
	env = convert_env(section->env);
	if (!env)
		return (free_matrice(arg), malloc_error(), ERROR);
	if (is_builtin(section))
	{
		data[SAVE_FD0] = dup(STDIN_FILENO);
		data[SAVE_FD1] = dup(STDOUT_FILENO);
		if (exec_builtins(section) == ERROR)
		{
			dup2(data[SAVE_FD0], STDIN_FILENO);
			dup2(data[SAVE_FD1], STDOUT_FILENO);
			close(data[TMP_FD0]);
			close(data[TMP_FD1]);
			return (free_matrice(arg), free_matrice(env), exit(EXIT_SUCCESS), ERROR);
		}
		garbage_collect();
		// dup2(data[SAVE_FD0], STDIN_FILENO);
		// dup2(data[SAVE_FD1], STDOUT_FILENO);
		// close(data[TMP_FD0]);
		// close(data[TMP_FD1]);
		exit(EXIT_SUCCESS);
	}
	else if (!section->abs_path)
	{
		cmd_not_found(section->cmd);
		close(data[TMP_FD0]);
		close(data[TMP_FD1]);
		garbage_collect();
		exit(SUCCESS);
	}
	else if (execve(section->abs_path, arg, env) == -1)
		return (free_matrice(env), free_matrice(arg), perror(section->cmd), exit(127), ERROR);
	free_matrice(arg);
	free_matrice(env);
	exit(130);
}

void end_of_pid(int *data)
{
	close(data[TMP_FD1]);
	if (data[I] > 0)
		close(data[PREV]);
	data[PREV] = data[TMP_FD0];
	// close(data[TMP_FD0]);
}

int conductor(t_section **section)
{
	pid_t *pid;
	t_section *tmp;
	int data[6];
	char **arg;
	char **env;

	data[PREV] = -1;
	data[I] = 0;
	tmp = *section;
	arg = NULL;
	env = NULL;
	if (tmp->deep == 1 && is_builtin(tmp) == 1)
	{
		data[SAVE_FD0] = dup(STDIN_FILENO);
		data[SAVE_FD1] = dup(STDOUT_FILENO);
		if (exec_builtins(tmp) == ERROR)
		{
			dup2(data[SAVE_FD0], STDIN_FILENO);
			dup2(data[SAVE_FD1], STDOUT_FILENO);
			close(data[SAVE_FD0]);
			close(data[SAVE_FD1]);
			return (ERROR); // tracked_free(pid), ERROR);
		}
		dup2(data[SAVE_FD0], STDIN_FILENO);
		dup2(data[SAVE_FD1], STDOUT_FILENO);
		close(data[SAVE_FD0]);
		close(data[SAVE_FD1]);
		return (SUCCESS);
	}
	else
	{
		pid = ft_calloc(tmp->deep, sizeof(int));
		if (!pid)
			return (malloc_error(), ERROR);
		while (data[I] < (*section)->deep) // && (*section)->deep != 1 && is_builtin(tmp) != 1)
		{
			pipe(data);
			pid[data[I]] = fork();
			if (pid[data[I]] == 0)
			{
				if (exec(tmp, pid, data, arg, env) == ERROR)
					return (ERROR);
			}
			else if (pid[data[I]] > 0)
				end_of_pid(data);
			tmp = tmp->next;
			free_matrice(arg);
			free_matrice(env);
			data[I]++;
		}
	}
	data[I] = 0;
	while (data[I] < (*section)->deep)
	{
		waitpid(pid[data[I]], NULL, 0);
		data[I]++;
	}
	close(data[TMP_FD0]);
	close(data[TMP_FD1]);
	free_list_section(section);
	return (SUCCESS);
}
