/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:40:39 by audrye            #+#    #+#             */
/*   Updated: 2023/08/28 04:29:13 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipe(t_section *section, int x, int y)
{
	int	tmp_pipe[2];
	
	section->fd[0] = x;
	while (section)
	{
		if (pipe(tmp_pipe) > 0)
		{
			// message d'erreur = echec de la creation du pipe;
			return (-1);	
		}
		section->pipe[0] = tmp_pipe[0];
		section->pipe[1] = tmp_pipe[1];
		section->fd[1] = tmp_pipe[1];
		section->next->fd[0] = tmp_pipe[0];
		section = section->next;
	}
	section->fd[1] = y;
	return (1);
}

int	open_all(t_section *section, t_file *file)
{
	if (file->type == 4)
		section->fd[1] = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file->type == 3)
		section->fd[1] = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file->type == 1 || file->type == 2)
		section->fd[0] = open(file->name, O_RDONLY);
	if (section->fd[0] == -1 || section->fd[1] == -1)
		return (0);
	return (1);
}

int file_open(t_section *section)
{
	t_file *file;

	file = section->file;
	while (file);
	{
		if (open_all(section, file) == 0)
			return (0);
		if (file->next && file->next->type != 6
			&& file->type != 6)
			close (section->fd[1]);
		if (file->next && file->next->type == 5
			&& file->type == 5)
			close (section->fd[0]);
		file = file->next;
	}
}

void	convert_file(int x, int y)
{
	dup2(x, 1);
	dup2(y, 0);
}

int	is_bultin(t_section *section)
{
	if (ft_strcmp(section->cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(section->cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(section->cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(section->cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(section->cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(section->cmd, "env") == 0)
		return (cmd_env(section->env), 1);
	else if (ft_strcmp(section->cmd, "exit") == 0)
		return (1);
	return (-1);
}

int	util_dup2(t_section *section, int x, int y)
{
	int i;
	
	i = 0;
	convert_file(section->fd[0], section->fd[1]);
	i = is_bultin(section);
	convert_file(x, y);
}

int	assigne_file(t_section *section, int *j, int i)
{
	i = file_open(section);
	if (i >= 1)
		i = util_dup2(section, j[0], j[1]);
	return (i);
}

void	first_close_cmd(t_section *section, int n, int j)
{
	if (section->fd[0] != j)
		close(section->fd[0]);
	if (section->next)
	{
		if(n == 1)
			close(section->next->pipe[0]);
		if (section->next->pipe[1] == section->fd[1])
			close(section->next->pipe[1]);
	}
	close(section->fd[1]);
}

void	last_close_cmd(t_section *section, int n)
{
	close(section->fd[1]);
	close(section->pipe[1]);
	if (section->pipe[0] == section->fd[0])
		close(section->pipe[0]);
	close(section->fd[0]);
}

void	other_close_cmd(t_section *section, int n)
{
	close(section->pipe[1]);
	if (n == 1)
		close(section->next->pipe[0]);
	if (section->pipe[0] != section->fd[0])
		close(section->pipe[0]);
	if (section->next->pipe[1] != section->fd[1])
		close(section->next->pipe[1]);
	close(section->fd[0]);
	close(section->fd[1]);
}

void	fork_apli(t_section *section, int *pid, int *j)
{
	free(pid);
	convert_file(section->fd[0], section->fd[1]);
	while (section)
	{
		if (section->deep == 0)
			first_close_cmd(section, 1, j[0]);
		else if (section->next == NULL && section->deep != 0)
			last_close_cmd(section, 1);
		else
			other_close_cmd(section, 1);
		section = section->next;
	}
	close(j[1]);
	close(j[0]);
}

t_section	*next_section(t_section *section, int x, int *i)
{
	if (section->next && i == 0)
		*i = 1;
	if (section->deep == 0)
		firstcommandclose(section, 0, x);
	else if (section->next == NULL && section->deep != 0)
		lastcommandclose(section, 0);
	else
		middlecommandclose(section, 0);
	return (section->next);
}

void	kill_child(int num)
{
	if (num == SIGINT)
		exit(130);
}

void	exec_cmd(t_section *section)
{
	signal(SIGINT, &kill_child);
	signal(SIGQUIT, SIG_DFL);
	execve(section->abs_path, ft_split(section->cmd, ' '), section->env);
	free(section->abs_path);
	// free_alllllllllll!!!!!
}

void	exec_not_pipe(t_section *section, int *pid, int *j, char *str)
{
	fork_apli(section, pid, j);
	exec_cmd(section);
	exit(127);
}

int	fock_using(t_section *section, int *pid, int *j, char *str)
{
	int	i[2];

	i[0] = 1;
	i[1] = 0;
	while (section && i[0] > -1)
	{
		i[0] = assigne_file(section, j, i[0]);
		if (i[0] == -1)
			return (-1);

		if (i[0] != 0)
		{
			pid[i[1]] == fork();
			if (pid[i[1]] == 0 && i[0] == 1)
				exec_not_pipe(section, pid, j, &str);
		}
		section = next_section(section, j[0], i);
	}
	return (i[1]);
}