/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:06:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/06 04:46:05 by audrye           ###   ########.fr       */
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

	while (token)
	{
		if (token->type == OUT)
			fd = open(token->str, O_CREAT | O_TRUNC, 0644);
		if (token->type == APPEND)
			fd = open(token->str, O_CREAT | O_APPEND, 0644);
		if (token->type == IN)
			fd = open(token->str, O_RDONLY);
		if (fd == -1)
			exit(1);
		if (token->type == OUT || token->type == APPEND)
			dup2(fd, STDOUT_FILENO);
		else 
			dup2(fd, STDIN_FILENO);
		if (!token->str)
			exit(1);
		token = token->next;
	}
	return (fd);
}

void	redirection(int fd[2], int index, int last, int prev, t_section *section)
{
	t_token *token;
	
	token = section->token;	
	if (index != 0)
	{
		dup2(prev, STDIN_FILENO);
		close(prev);
	}
	if (index != last)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
//	pour heredoc / in, out / append
	openfiles(token);
	
	// int fd;
	// while (fichier[i])
	// {
	// 	if (type[i] == OUT)
	// 	{
	// 		fd = open(fichier[i], O_CREAT | O_TRUNC, 0644);
	// 	}
	// 	if (type[i] == APPEND)
	// 	{
	// 		fd = open(fichier[i], O_CREAT | O_APPEND, 0644);
	// 	}
	// 	if (type[i] == IN)
	// 	{
	// 		fd = open(fichier[i], O_RDONLY);
	// 	}
	// 	if (fd == -1)
	// 		exit(1);;
	// 	if (type[i] == OUT || type[i] == APPEND)
	// 		dup2(fd, STDOUT_FILENO);
	// 	else 
	// 		dup2(fd, STDIN_FILENO);
	// }
	// if (!cmd)
	// 	exit(1);
	// // je lis dans minishell.c
	// // jecris dans c
	// execve()
}

int	exec(t_section *section, int *fd, int *pid, int i, int prev)
{
	char	**arg;
	char	**env;
	
	free(pid);
	// printf("dans le fork\n");
	redirection(fd, i, section->deep - 1, prev, section);
	arg = ft_split(section->option, ' ');
	env = convert_env(section->env);
	if (execve(section->abs_path, arg, env) == -1)
		perror(section->option);
	// fprintf(stderr, "%s command not found\n", section->cmd);
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
	int			prev;
	int			i;
	
	prev = -1;	
	i = 0;
	tmp = *section;
	pid = ft_calloc(tmp->deep, sizeof(int));
	if (!pid)
		return (malloc_error(), ERROR);
	while (i < (*section)->deep)
	{
		pipe(tmpfd);
		if (find_path(tmp) != SUCCESS)
			return (free_list_section(section), ERROR);
		pid[i] = fork();
		if (pid[i] == 0)
			exec(tmp , tmpfd, pid, i, prev);
		else if (pid[i] > 0)
		{
			// fprintf(stderr, "%i %i %i\n", tmpfd[0], tmpfd[1], prev);
			end_of_pid(tmpfd, i, &prev);
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < (*section)->deep)
		waitpid(pid[i++], NULL, 0);
	close(tmpfd[0]);
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