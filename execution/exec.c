/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:06:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 13:38:57 by ntardy           ###   ########.fr       */
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

int	redirection(int *data, int last, t_section *section)
{
	t_token	*token;
	int		redir;

	redir = 0;
	token = section->token;
	if (is_heredoc(token) == 1)
	{
		if (all_heredoc(token, *(section->env)) == ERROR)
			return (tracked_close(data[TMP_FD0]), tracked_close(data[TMP_FD1]), free_list_section(&section), ERROR); // RETURN UNE VRAIE VALEUR
	}
	if (is_builtin(section) && section->deep == 1)
		redir = openfiles_builtins(token);
	else
		redir = openfiles(token);
	if (section->deep == 1 && redir < 0)
		return (ERROR);
	if (redir >= 0)
		data[TMP_FD1] = redir;
	if (data[I] != 0)
	{
		dup2(data[PREV], STDIN_FILENO);
		tracked_close(data[PREV]);
	}
	if (data[I] != last)
		dup2(data[TMP_FD1], STDOUT_FILENO);
	if (section->deep != 1)
		tracked_close(data[TMP_FD0]);
	tracked_close(data[TMP_FD1]);
	return (SUCCESS);
}

int exec(t_section *section, int *pid, int *data, char **arg, char **env)
{
	tracked_free(pid);
	find_path(section);
	redirection(data, section->deep - 1, section);
	arg = ft_split(section->option, ' ');
	if (!arg)
		return (ERROR);
	env = convert_env(section->env);
	if (!env)
		return (free_matrice(arg), ERROR);
	collect_fd();
	if (is_builtin(section))
	{
		data[SAVE_FD0] = dup(STDIN_FILENO);
		data[SAVE_FD1] = dup(STDOUT_FILENO);
		add_fd_garbage(data[SAVE_FD0]);
		add_fd_garbage(data[SAVE_FD1]);
		if (exec_builtins(section) == ERROR)
		{
			dup2(data[SAVE_FD0], STDIN_FILENO);
			dup2(data[SAVE_FD1], STDOUT_FILENO);
			tracked_close(data[SAVE_FD0]);
			tracked_close(data[SAVE_FD1]);
			// garbage_collect();
			collect_fd();
			return (exit(EXIT_SUCCESS), ERROR);
		}
		// garbage_collect();
		collect_fd();
		collect_ptr();
		exit(SUCCESS);
		// cmd_exit(g_error);//METTRE UNE VRAIE VALEUR
	}
	else if (!section->abs_path)
	{
		cmd_not_found(section->cmd);
		// tracked_close(data[TMP_FD0]);
		// tracked_close(data[TMP_FD1]);
		// garbage_collect();
		collect_fd();
		collect_ptr();
		exit(SUCCESS);
	}
	else if (execve(section->abs_path, arg, env) == -1)
		return (free_matrice(env), free_matrice(arg), exit(127), ERROR);
	return (SUCCESS);
}

void end_of_pid(int *data)
{
	tracked_close(data[TMP_FD1]);
	if (data[I] > 0)
		tracked_close(data[PREV]);
	data[PREV] = data[TMP_FD0];
	// close(data[TMP_FD0]);
}

void	print_data(int data[6])
{
	if (!data)
		return ;
	printf("TMP_FD0 = %d\n", data[TMP_FD0]);
	printf("TMP_FD1 = %d\n", data[TMP_FD1]);
	printf("I = %d\n", data[I]);
	printf("PREV = %d\n", data[PREV]);
	printf("SAVE_FD0 = %d\n", data[SAVE_FD0]);
	printf("SAVE_FD1 = %d\n", data[SAVE_FD1]);
}

void	init_data(int data[6])
{
	data[PREV] = -1;
	data[I] = 0;
	data[TMP_FD0] = 0;
	data[TMP_FD1] = 0;
	data[SAVE_FD0] = 0;
	data[SAVE_FD1] = 0;
}

int conductor(t_section **section)
{
	pid_t *pid;
	t_section *tmp;
	int data[6];
	char **arg;
	char **env;

	init_data(data);
	tmp = *section;
	arg = NULL;
	env = NULL;
	if (tmp->deep == 1 && is_builtin(tmp) == 1)
	{
		data[SAVE_FD0] = dup(STDIN_FILENO);
		data[SAVE_FD1] = dup(STDOUT_FILENO);
		add_fd_garbage(data[SAVE_FD0]);
		add_fd_garbage(data[SAVE_FD1]);
		if (redirection(data, (*section)->deep - 1, *section) == ERROR)
			return (NEW_LINE);
		if (exec_builtins(tmp) == ERROR)
		{
			dup2(data[SAVE_FD0], STDIN_FILENO);
			dup2(data[SAVE_FD1], STDOUT_FILENO);
			tracked_close(data[SAVE_FD0]);
			tracked_close(data[SAVE_FD1]);
			return (ERROR); // tracked_free(pid), ERROR);
		}
		dup2(data[SAVE_FD0], STDIN_FILENO);
		dup2(data[SAVE_FD1], STDOUT_FILENO);
		tracked_close(data[SAVE_FD0]);
		tracked_close(data[SAVE_FD1]);
		return (SUCCESS);
	}
	else
	{
		pid = ft_calloc(tmp->deep, sizeof(int));
		if (!pid)
			return (ERROR);
		while (data[I] < (*section)->deep) // && (*section)->deep != 1 && is_builtin(tmp) != 1)
		{
			pipe(data);
			add_fd_garbage(data[TMP_FD0]);
			// printf("%d\n\n\n", data[TMP_FD0]);
			add_fd_garbage(data[TMP_FD1]);
			// printf("%d\n\n\n", data[TMP_FD1]);
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
	// collect_fd();
	tracked_free(pid);
	free_list_section(section);
	return (SUCCESS);
}
