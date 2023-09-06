/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 06:31:49 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/06 01:02:54 by audrye           ###   ########.fr       */
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
		return (malloc_error(), NULL);
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
	(*section)->abs_path = ft_strjoin_path(path, (*section)->cmd);
	if (!(*section)->abs_path)
		return (malloc_error(), ERROR);
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
	matrix_path = ft_split(path, ':');
	if (!matrix_path)
		return (malloc_error(), ERROR);
	while (matrix_path[i])
	{
		return_val = check_path(matrix_path[i], &tmp);
		if (return_val == ERROR)
			return (ERROR);
		if (return_val == SUCCESS)
			break;
		i++;
	}
	return (return_val);
}

int	find_path(t_section *section)
{
	t_section	*tmp;
	char		*path;
	int			return_val;
	int			final_return;

	final_return = NEWLINE;
	tmp = section;
	path = getenv("PATH");
	while (tmp)
	{
		return_val = valid_path(path, tmp);
		printf("return_val = %d\n", return_val);
		printf("final_return = %d\n", final_return);
		if (return_val == ERROR)
			return (ERROR);
		else if (return_val == SUCCESS || is_builtin(tmp))
			final_return = SUCCESS;
		tmp = tmp->next;
	}
	return (final_return);
}
