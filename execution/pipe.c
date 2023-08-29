/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:40:39 by audrye            #+#    #+#             */
/*   Updated: 2023/08/29 15:09:25 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipe(t_section *section, int x, int y)
{
	int	tmp_pipe[2];
	
	section->fd[0] = y;
	// printf("vas dans exec_pipe\n");
	while (section->next)
	{
		// printf("entre dans la boucle \n");
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
	section->fd[1] = x;
	// printf("ici\n");
	return (1);
}

int	open_all(t_section *section, t_file *file)
{
	// printf("valeur 1 de section->fd[0] = %d \t|\t section->fd[1] = %d\n", section->fd[0], section->fd[1]);
	// printf("valeur de file->name = %s\n", file->name);
	if (file->type == OUT)
	{
		// printf("OUT\n");
		section->fd[1] = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (file->type == APPEND)
	{
		// printf("APPEND\n");
		section->fd[1] = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (file->type == IN || file->type == HEREDOC)
	{
		// printf("IN ou HEREDOC\n");
		section->fd[0] = open(file->name, O_RDONLY);
	}
	// printf("valeur 2 de section->fd[0] = %d \t|\t section->fd[1] = %d\n", section->fd[0], section->fd[1]);
	if (section->fd[0] == -1 || section->fd[1] == -1)
		return (0);
	return (1);
}

int file_open(t_section *section)
{
	t_file *file;

	file = section->file;
	// printf("valeur avent open_all de file->name =\n");
	while (file != NULL)
	{
		if (open_all(section, file) == 0)
		{
			// printf("vas dans open all\n");
			return (0);
		}
		if (file->next && file->next->type != HEREDOC && file->next->type != IN && file->type != HEREDOC && file->type != IN)
		{
			// printf("vas dans le premier close\n");
			close (section->fd[1]);
		}
		if (file->next && file->next->type == IN && file->next->type == HEREDOC && file->type == IN && file->type == HEREDOC)
		{
			// printf("vas dans le deuxieme close\n");
			close (section->fd[0]);
		}
		file = file->next;
	}
	return (1);
}

void	convert_file(int x, int y)
{
	dup2(y, 1);
	dup2(x, 0);
}

int	is_bultin(t_section *section)
{
	printf("est dans is_bultin\n");
	if (ft_strcmp(section->cmd, "echo") == 0)
		ft_echo(section);
	else if (ft_strcmp(section->cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(section->cmd, "env") == 0)
		cmd_env(section->env);
	else if (ft_strcmp(section->cmd, "exit") == 0)
		return (0);
	else
		return (1);
	if (section->next)
		return (2);
	return (0);
}

int	util_dup2(t_section *section, int x, int y)
{
	int i;
	
	convert_file(section->fd[0], section->fd[1]);
	printf("avant is bultin\n");
	i = is_bultin(section);
	convert_file(x, y);
	return (i);
}

int	assigne_file(t_section *section, int *j, int i)
{
	i = file_open(section);
	printf("valeur 1 de i = %d\n", i);
	if (i >= 1)
		i = util_dup2(section, j[0], j[1]);
	// printf("valeur 2 de i = %d\n", i);
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
		if (section->next->pipe[1] != section->fd[1])
			close(section->next->pipe[1]);
	}
	close(section->fd[1]);
}

void	last_close_cmd(t_section *section)
{
	close(section->fd[1]);
	close(section->pipe[1]);
	if (section->pipe[0] != section->fd[0])
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
			last_close_cmd(section);
		else
			other_close_cmd(section, 1);
		section = section->next;
	}
	close(j[0]);
	close(j[1]);
}

t_section	*next_section(t_section *section, int x, int *i)
{
	if (section->next && i == 0)
		*i = 1;
	if (section->deep == 0)
		first_close_cmd(section, 0, x);
	else if (section->next == NULL && section->deep != 0)
		last_close_cmd(section);
	else
		other_close_cmd(section, 0);
	return (section->next);
}

void	kill_child(int num)
{
	if (num == SIGINT)
		exit(130);
}

char	**ft_get_env_bis(t_env	**env)
{
	char	**env_tmp;
	t_env	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tmp = *env;
	while (tmp)
	{
		k++;
		tmp=tmp->next;
	}
	env_tmp = ft_calloc((k + 1), sizeof(char *));
	if (!env_tmp)
		return(NULL); //FREEEEEALLALALALALAL
	tmp = *env;
	while (tmp)
	{
		k = 0;
		env_tmp[i] = ft_calloc((ft_strlen(tmp->name) + ft_strlen(tmp->content) + 3), sizeof(char));
		if (!env_tmp[i])
			return (NULL); //FREE ALLLLLLL
		j = 0;
		while (tmp->name[j])
		{
			env_tmp[i][k] = tmp->name[j];
			k++;
			j++;
		}
		j = 0;
		env_tmp[i][k++] = '=';
		while (tmp->content[j])
			env_tmp[i][k++] = tmp->content[j++];
		i++;
		tmp = tmp->next;
	}
	return (env_tmp);
}

void free_env_char(char **env)
{
	int i;
	
	i = 0;
	while (env)
		free(env[i++]);
	free(env);
}

void	exec_cmd(t_section *section)
{
	char **env_tmp;
	
	env_tmp = ft_get_env_bis(section->env);
	signal(SIGINT, &kill_child);
	signal(SIGQUIT, SIG_DFL);
	execve(section->abs_path, ft_split(section->option, ' '), env_tmp);
	free(section->abs_path);
	// free_alllllllllll!!!!!
}

void	exec_not_pipe(t_section *section, int *pid, int *j)
{
	fork_apli(section, pid, j);
	// printf("exec_pipe\n");
	exec_cmd(section);
	exit(127);
}

void	you_pipe(int *pid, int y, t_section *section)
{
	if (pid[y] < 0)
		// printf("erreur de pipe\n");
	if (section->abs_path)
		free(section->abs_path);
}

int	fork_using(t_section *section, int *pid, int *j)
{
	int	i[2];

	i[1] = 0;
	i[0] = 1;
	printf("valeur de file->name \n");
	while (section && i[0] > -1)
	{
		i[0] = assigne_file(section, j, i[0]);
		printf("rentre dans le ift valeur de i[0] = %d\n", i[0]);
		if (i[0] == -1)
			return (-1);
		if (i[0] == 1)
		{
			// printf("rentre dans le if \n");
			// i[0] = is_clear(token, section);
			// printf("valeur de i[]0 = %d\n", i[0]);
			// printf("valeur option = %s\n", section->option);
			if (i[0] == -1)
				return (free(section->option), i[0]);
			if (i[0] != 0)
			{
				pid[i[1]] = fork();
				if (pid[i[1]] == 0 && i[0] == 1)
					exec_not_pipe(section, pid, j);
				you_pipe(pid, i[1]++, section);
			}
		}
		section = next_section(section, j[0], i);
	}
	return (i[1]);
}