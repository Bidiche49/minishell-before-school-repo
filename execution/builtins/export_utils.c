/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:34:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 09:59:23 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	contain_equal(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '=')
			return (1);
	return (0);
}

void	error_export(char *line)
{
	g_error = 1;
	err("export `");
	err(line);
	err("' : not a valid identifier\n");
}

int	check_var_name(char *line)
{
	int	i;

	i = 1;
	if (is_num(line[0]) || ((line[0] < 'A' || (line[0] > 'Z'
			&& line[0] < 'a') || line[0] > 'z')
			&& line[0] != '_'))
		return (0);
	while (line[i] && (is_alnum_und(line[i])))
		i++;
	if (!line[i])
		return (1);
	else if (line[i] == '=')
		return (i);
	return (0);
}

int	existing_var(t_env **env, char *line)
{
	t_env	*tmp;
	int		len_name;

	tmp = *env;
	len_name = ft_strlen_char(line, '=');
	while(tmp)
	{
		if (ft_strncmp(line, tmp->name, len_name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char **fill_split_line(char *line_env)
{
	while (*line_env && *line_env != ' ')
		line_env++;
	if (*line_env == ' ')
		line_env++;
	return (ft_split(line_env, ' '));
}
