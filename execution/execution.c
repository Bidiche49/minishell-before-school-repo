/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/29 15:21:07 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	is_bubul(char *src)
{
	if (ft_strcmp(src, "export") == 0 || ft_strcmp(src, "echo") == 0 || ft_strcmp(src, "cd") == 0 || ft_strcmp(src, "pwd") == 0 || ft_strcmp(src, "unset") == 0 || ft_strcmp(src, "env") == 0 || ft_strcmp(src, "exit") == 0)
		return (0);
	return (1);
}

int	check_cmd(char *src, char *env, t_section *section)
{
	char	**tmp;
	int	i;

	i = 0;
	tmp = ft_split(env, ':');
	if (is_bubul(src) == 0)
	{
		if (ft_strcpy_token(src, section) != 0)
				return (ERROR);
		return (SUCCESS);
	}	
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

char	*ft_get_env(t_env	**env, char *str)
{
	char	*res;
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = *env;
	while (tmp && ft_strcmp(tmp->name, str) != 0)
		tmp=tmp->next;
	if (tmp == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(tmp->name) + ft_strlen(tmp->content) + 2));
	if (!res)
		return (NULL); //FREE ALLLLLLL
	while (tmp->name[j])
		res[i] = tmp->name[j++];
	j = 0;
	res[i] = '=';
	while (tmp->content[j])
		res[i++] = tmp->content[j++];
	res[i] = '\0';
	return (res);
}

void	find_cmd(t_token *token, t_section *section)
{
	char	*path;
	
	path = ft_get_env(section->env, "PATH");
	if (!path)
		return ;
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
}

int	gathering(t_token *token, t_section *section) // foction a refaire ainsi que cest sous fontion
{
	while (token && token->type != PIPE)
	{
		if (token->type == SEPARATOR)
			add_space(section);
		else if (token->type == WORD || token->type == S_QUOTES || token->type == D_QUOTES)
		{
			section->option = ft_strjoin(section->option, token->str);
			if (section->option == NULL)
				return (ERROR);
		}
		token = token->next;
	}
	return (SUCCESS);
}

int	is_clear(t_token *token, t_section *section)
{
	printf("in is_clear\n");
	while (section)
	{
		if (token->type == PIPE)
			section = section->next;
		if (section->cmd != NULL)
		{
			if (gathering(token, section) != 0)
				return (-1);
		}
		section = section->next;
	}
	return (0);
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
	printf("est dans master exec\n");
	pid[0] = -1;
	j[1] = dup(1);
	j[0] = dup(0);	// printf("passe signal\n");

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
	t_file		list_file;
	
	init_file(token, &list_file);
	init_list_section(token, &list_section, env);
	find_cmd(token, &list_section);
	printf("section->cmd = %s\n", list_section.cmd);
	printf("init done\n");
	if (is_clear(token, &list_section) != 0) // scan des differents token et verification de la validation des commandes
		return (ERROR); // free la structure
	// printf("valeur de cmd = %s \t||\t valeur de absPath = %s \t|| \t valeur des option = %s\n", list_section.cmd, list_section.abs_path, list_section.option);
	printf("avant\n");
	if (master_exec(&list_section) == -1)
		return (ERROR);
	return (SUCCESS);
}
