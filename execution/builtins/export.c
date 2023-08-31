/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:30:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/31 12:34:17 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_line(char *line)
{
	int	i;

	i = check_var_name(line);
	if (i == 0)
		return (error_export(line), 0);
	return (1);
}

int	mod_exist_var(t_env **env, char *line)
{
	t_env	*tmp;
	int		len_name;
	char	*name;

	tmp = *env;
	len_name = ft_strlen_char(line, '=');
	name = line;
	name[len_name] = '\0';
	while(tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (tmp->content)
				free(tmp->content);
			tmp->content = ft_strdup(line + len_name + 1);
			if (!tmp->content)
				return (malloc_error(), ERROR);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_env(t_env **env, char **split_line)
{
	int	i;

	if (!split_line)
		return (malloc_error(), ERROR);
	i = 0;
	while (split_line && split_line[i] && split_line[i][0])
	{
		if (existing_var(env, split_line[i]))
		{
			if (mod_exist_var(env, split_line[i]) == ERROR)
				return (ERROR);
		}
		else if (check_line(split_line[i]))
		{
			if (ft_lstadd_back_env(env, fill_new_env(split_line[i])))
			{
				free_matrice(split_line);
				return (malloc_error(), ERROR);
			}
		}
		i++;
	}
	return (free_matrice(split_line), SUCCESS);
}

void	print_env_export(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if (tmp->name && tmp->content)
		{
			printf(BOLD YELLOW "export" RESET);
			printf(YELLOW " %s=" RESET, tmp->name);
			printf(CYAN "\"%s\"\n" RESET, tmp->content);
		}
		if (tmp->name && !tmp->content)
		{
			printf(BOLD YELLOW "export" RESET);
			printf(YELLOW " %s\n" RESET, tmp->name);
		}
		tmp = tmp->next;
	}
}

int	cmd_export(t_env **env, char *line_env)
{
	if (!line_env)
		return (ERROR);
	if (!ft_strcmp(line_env, "export"))
		return (print_env_export(env), SUCCESS);
	if (add_env(env, fill_split_line(line_env)) == ERROR)
		return (ERROR);//FREE ALL---------------------------------------------------
	return (SUCCESS);
}
