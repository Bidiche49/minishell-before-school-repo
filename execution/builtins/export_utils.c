/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:34:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 22:42:34 by ntardy           ###   ########.fr       */
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
	msg("export `");
	msg(line);
	msg("' : not a valid identifier\n");
}

int	check_var_name(char *line)
{
	int	i;

	i = 1;
	if (is_num(line[0]) || !is_alnum_und(line[0]))
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
	char	is_equals;
	char	*name;

	tmp = *env;
	len_name = ft_strlen_char(line, '=');
	name = line;
	is_equals = name[len_name];
	name[len_name] = '\0';
	while(tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (name[len_name] = is_equals, 1);
		tmp = tmp->next;
	}
	return (name[len_name] = is_equals, 0);
}

char **fill_split_line(char *line_env)
{
	int	i;

	i = 0;
	if (!line_env)
		return (NULL);
	while (line_env[i] && line_env[i] != ' ')
		i++;
	if (line_env[i] && line_env[i] == ' ')
		i++;
	return (ft_split(line_env + i, ' '));
}
