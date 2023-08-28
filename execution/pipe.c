/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:40:39 by audrye            #+#    #+#             */
/*   Updated: 2023/08/29 00:01:09 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipe(t_section *section, int x, int y)
{
	int	tmp_pipe[2];
	
	section->fd[0] = y;
	while (section->next)
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
	section->fd[1] = x;
	return (1);
}

int	open_all(t_section *section, t_token *token)
{
	if (token->type == OUT)
		section->fd[1] = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (token->type == APPEND)
		section->fd[1] = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (token->type == IN || token->type == HEREDOC)
		section->fd[0] = open(token->str, O_RDONLY);
	if (section->fd[0] == -1 || section->fd[1] == -1)
		return (0);
	return (1);
}

int file_open(t_section *section)
{
	t_token *token;

	token = section->token;
	while (token)
	{
		if (open_all(section, token) == 0)
			return (0);
		if (token->next && token->next->type != HEREDOC && token->next->type != IN && token->type != HEREDOC && token->type != IN)
			close (section->fd[1]);
		if (token->next && token->next->type == IN && token->next->type == HEREDOC && token->type == IN && token->type == HEREDOC)
			close (section->fd[0]);
		token = token->next;
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
		return (ft_echo(section), 0);
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
	i = is_bultin(section);
	convert_file(x, y);
	return (i);
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

char	**ft_get_env(t_env	*env)
{
	char	**env_tmp;
	t_env	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (tmp)
	{
		k++;
		tmp=tmp->next;
	}
	env_tmp = malloc(sizeof(char *) * (k + 1));
	if (!env_tmp)
		return(NULL); //FREEEEEALLALALALALAL
	tmp = env;
	while (tmp)
	{
		env_tmp[i] = malloc(sizeof(char) * (ft_strlen(tmp->name) + ft_strlen(tmp->content) + 2));
		if (!env_tmp[i])
			return (NULL); //FREE ALLLLLLL
		printf("name = %s", tmp->name);
		while (tmp->name[j])
			env_tmp[i][k++] = tmp->name[j++];
		j = 0;
		env_tmp[i][k++] = '=';
		printf(" = %s\n", tmp->content);
		while (tmp->content[j])
			env_tmp[i][k++] = tmp->content[j++];
		env_tmp[i][k] = '\0';
		tmp=tmp->next;
	}
	env_tmp[i] = '\0';
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
	
	env_tmp = ft_get_env(*section->env);
	signal(SIGINT, &kill_child);
	signal(SIGQUIT, SIG_DFL);
	execve(section->abs_path, ft_split(section->cmd, ' '), env_tmp);
	free(section->abs_path);
	// free_alllllllllll!!!!!
}

void	exec_not_pipe(t_section *section, int *pid, int *j)
{
	fork_apli(section, pid, j);
	exec_cmd(section);
	exit(127);
}

void	you_pipe(int *pid, int y, t_section *section)
{
	if (pid[y] < 0)
		printf("erreur de pipe\n");
	if (section->abs_path)
		free(section->abs_path);
}

int	fork_using(t_section *section, int *pid, int *j)
{
	int	i[2];

	i[1] = 0;
	i[0] = 1;
	while (section && i[0] > -1)
	{
		i[0] = assigne_file(section, j, i[0]);
		if (i[0] == -1)
			return (-1);
		if (i[0] != 0)
		{
			pid[i[1]] = fork();
			if (pid[i[1]] == 0 && i[0] == 1)
				exec_not_pipe(section, pid, j);
			you_pipe(pid, i[1]++, section);
		}
		section = next_section(section, j[0], i);
	}
	return (i[1]);
}