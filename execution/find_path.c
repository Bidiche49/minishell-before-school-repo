/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 06:31:49 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 21:25:40 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_strjoin_path(char *s1, char *s2)
{
	char		*res;
	int			i;
	int const	j = ft_strlen(s1);

	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (s1);
	res = ft_calloc((j + ft_strlen(s2) + 2), sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i] = '/';
	i =  -1;
	while (s2[++i])
		res[j + i + 1] = s2[i];
	return (res);
}

int	check_path(char *path, t_section **section)
{
	// printf("section->cmd = %s\n", (*section)->cmd);
	if (!access((*section)->cmd, F_OK))
	{
		if (!access((*section)->cmd, X_OK))
		{
			printf("cmd = %s\n", (*section)->cmd);
			(*section)->abs_path = ft_strdup((*section)->cmd);
			if (!(*section)->abs_path)
				return (ERROR);
			return(SUCCESS);
		}
	}
	if ((*section)->abs_path)
	{
		tracked_free((*section)->abs_path);
		(*section)->abs_path = NULL;
	}
	(*section)->abs_path = ft_strjoin_path(path, (*section)->cmd);
	if (!(*section)->abs_path)
		return (ERROR);
	if (!access((*section)->abs_path, F_OK))
		if (!access((*section)->abs_path, X_OK))
			return (SUCCESS);
	return (NEW_LINE);
}

int	valid_path(char *path, t_section *tmp)
{
	int		i;
	int		return_val;
	char	**matrix_path;

	i = 0;
	if (!path && !is_builtin(tmp))
		return (NEW_LINE);
	if (!tmp->cmd)
		return (SUCCESS);
	matrix_path = ft_split(path, ':');
	if (!matrix_path)
		return (ERROR);
	while (matrix_path[i])
	{
		return_val = check_path(matrix_path[i], &tmp);
		if (return_val == ERROR)
			return (free_matrice(matrix_path), ERROR);
		if (return_val == SUCCESS)
			return (free_matrice(matrix_path), SUCCESS);
		i++;
	}
	if (tmp->abs_path)
	{
		tracked_free(tmp->abs_path);
		tmp->abs_path = NULL;
	}
	return (free_matrice(matrix_path), return_val);
}

char	*ft_get_path(t_env	**env)
{
	char	*path;
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = *env;
	while (tmp && ft_strcmp(tmp->name, "PATH") != 0)
		tmp=tmp->next;
	path = ft_calloc((ft_strlen(tmp->name) + ft_strlen(tmp->content) + 2), sizeof(char));
	if (!path)
		return (NULL); //FREE ALLLLLLL
	while (tmp->name[j])
		path[i] = tmp->name[j++];
	j = 0;
	path[i] = '=';
	while (tmp->content[j])
		path[i++] = tmp->content[j++];
	return (path);
}

int	find_path(t_section *section)
{
	t_section	*tmp;
	char		*path;
	int			return_val;
	int			final_return;

	final_return = NEW_LINE;
	tmp = section;
	path = ft_get_path(section->env);
	if (!path)
		return (ERROR);
	while (tmp)
	{
		return_val = valid_path(path, tmp);
		if (return_val == ERROR)
			return (tracked_free(path), ERROR);
		else if (return_val == SUCCESS || is_builtin(tmp))
			final_return = SUCCESS;
		tmp = tmp->next;
	}
	return (tracked_free(path), final_return);
}
