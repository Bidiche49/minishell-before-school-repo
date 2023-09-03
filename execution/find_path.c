/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:09:13 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 00:55:46 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcat_path(char *path, char *cmd, t_section *section)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(path) + ft_strlen(cmd);
	free(section->abs_path);
	section->abs_path = malloc(sizeof(char) * (len + 2));
	if (!section->abs_path)
		return (ERROR);
	while (path[i])
	{
		section->abs_path[i] = path[i];
		i++;
	}
	section->abs_path[i++] = '/';
	while (cmd[j])
	{
		section->abs_path[i] = cmd[j];
		i++;
		j++;
	}
	section->abs_path[i] = '\0';
	return (SUCCESS);
}

int is_bubul(char *src)
{
	if (ft_strcmp(src, "export") == 0 || ft_strcmp(src, "echo") == 0 || ft_strcmp(src, "cd") == 0 || ft_strcmp(src, "pwd") == 0 || ft_strcmp(src, "unset") == 0 || ft_strcmp(src, "env") == 0 || ft_strcmp(src, "exit") == 0)
		return (0);
	return (1);
}

int check_path(char *src, char *env, t_section *section)
{
	char **tmp;
	int i;

	i = 0;
	tmp = ft_split(env, ':');
	if (is_bubul(src) == 0)
		return (SUCCESS);
	while (tmp[i])
	{
		if (ft_strcat_path(tmp[i], src, section) != 0)
			return (ERROR);
		if (access(section->abs_path, F_OK) != -1)
		{
			if (access(section->abs_path, X_OK) != -1)
				return (SUCCESS);
		}
		i++;
	}
	return (SUCCESS);
}

void	find_path(t_section *section)
{
	char *path;

	path = ft_get_env(section->env, "PATH");
	if (!path)
		return;
	while (section)
	{
		if (section->cmd)
			check_path(section->cmd, path, section);
		section = section->next;
	}
}
