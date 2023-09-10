/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:06:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/10 12:02:16 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_lstsize_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

 int	ft_lstsize_section(t_section *section)
{
	int	i;

	i = 0;
	while (section)
	{
		section = section->next;
		i++;
	}
	return (i);
}

char	*cpy_new_line(char *tmp, char *s1, char *s2)
{
	int	i;
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

char	**convert_env(t_env **env)
{
	char	**env_tmp;
	t_env	*tmp;
	int		i;
	int		size;

	i = 0;
	tmp = *env;
	env_tmp = ft_calloc((ft_lstsize_env(*env) + 1), sizeof(char *));
	if (!env_tmp)
		return(NULL); //FREEEEEALLALALALALAL
	tmp = *env;
	while (tmp)
	{
		size = ft_strlen(tmp->name) + ft_strlen(tmp->content);
		env_tmp[i] = ft_calloc((size + 3), sizeof(char));
		if (!env_tmp[i])
			return (free_matrice(env_tmp), NULL); //FREE ALLLLLLL
		env_tmp[i] = cpy_new_line(env_tmp[i], tmp->name, tmp->content);
		i++;
		tmp = tmp->next;
	}
	return (env_tmp);
}

int	openfiles(t_token *token)
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
			if (token->type == IN)
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

void	redirection(int fd[2], int index, int last, int prev, t_section *section)
{
	t_token *token;
	int		redir;
	
	token = section->token;
	redir = openfiles(token);
	if (redir >= 0)
		fd[1] = redir;
	if (index != 0)
	{
		dup2(prev, STDIN_FILENO);
		close(prev);
	}
	if (index != last)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	exec(t_section *section, int *fd, int *pid, int i, int prev)
{
	char	**arg;
	char	**env;

	free(pid);
	redirection(fd, i, section->deep - 1, prev, section);
	if (is_builtin(section) == 1)
	{
		exec_builtins(section);
		exit(127);
	}
	arg = ft_split(section->option, ' ');
	env = convert_env(section->env);
	execve(section->abs_path, arg, env);
	exit(127);
}

void	end_of_pid(int *fd, int i, int *prev)
{
	close(fd[1]);
	if (i > 0)
		close(*prev);
	*prev = fd[0];

}

int	conductor(t_section **section)
{
	pid_t		*pid;
	t_section	*tmp;
	int			tmpfd[2];
	int			savefd[2];
	int			prev;
	int			i;

	prev = -1;
	i = 0;
	tmp = *section;
	pid = ft_calloc(tmp->deep, sizeof(int));
	if (!pid)
		return (malloc_error(), ERROR);
	savefd[0] = dup(STDIN_FILENO);
	savefd[1] = dup(STDOUT_FILENO);
	while (i < (*section)->deep)
	{
		pipe(tmpfd);
		// if (!is_builtin(tmp) && find_path(tmp) != SUCCESS)
		// 	return (1);
		pid[i] = fork();
		if (pid[i] == 0)
			exec(tmp , tmpfd, pid, i, prev);
		else if (pid[i] > 0)
			end_of_pid(tmpfd, i, &prev);
		dup2(savefd[0], STDIN_FILENO);
		dup2(savefd[1], STDOUT_FILENO);
		close(savefd[0]);
		close(savefd[1]);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < (*section)->deep)
		waitpid(pid[i++], NULL, 0);
	close(tmpfd[0]);
	free_list_section(section);
	return (SUCCESS);
}


/*

checker la syntax
si elle est pas bonne
	on recommence
fork()
	tokenize
	redirection
		tout rediriger
		if (!)
			exit(1);
	chercher si la commande existe
		execute

*/
