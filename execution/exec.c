/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:06:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/03 23:44:26 by audrye           ###   ########.fr       */
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

int	exec(t_section **section, int *pid)
{
	char	**matrix_env;
	char	**matrix_option;

	matrix_env = convert_env((*section)->env);
	if (!matrix_env)
		return (malloc_error(), ERROR);
	matrix_option = ft_split((*section)->option, ' ');
	if (!matrix_option)
		return (malloc_error(), ERROR);
	if (pid[0] == -1)
	{
		perror("fork");
		return ERROR;
	}
	if (pid[0] == 0)
	{
		execve((*section)->abs_path, matrix_option, matrix_env);
		free_section((*section));
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		waitpid(pid[0], &status, 0);
		// exit(127);
		// return (msg(ERR_FORK), g_error = FORK_KO, ERROR);
	}
	return (SUCCESS);
}

int	conductor(t_section **section)
{
	pid_t	*pid;

	pid = ft_calloc(ft_lstsize_section(*section), sizeof(int));
	if (!pid)
		return (malloc_error(), ERROR);
	int i = 0;
	pid[0] = fork();
	printf("deep = %d\n", (*section)->deep);
	if ((*section)->deep == 1)
		if (exec(section, pid) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
