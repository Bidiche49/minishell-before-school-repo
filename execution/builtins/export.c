/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:30:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 09:59:11 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_line(char *line)
{
	int	i;

	i = check_var_name(line);
	if (i == 0)
		return (error_export(line), 1);
	return (1);
}

int	mod_exist_var(t_env **env, char *line)
{
	t_env	*tmp;
	int		len_name;

	tmp = *env;
	len_name = ft_strlen_char(line, '=');
	while(tmp)
	{
		if (ft_strncmp(line, tmp->name, len_name))
		{
			if (tmp->content)
				free(tmp->content);
			tmp->content = ft_strdup(line + len_name + 1);
			if (!tmp->content)
				return (g_error = MALL_KO, err(ERR_MALLOC_KO), ERROR);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_env(t_env **env, char **split_line)
{
	int	i;

	i = 0;
	if (!split_line)
		return (g_error = MALL_KO, err(ERR_MALLOC_KO), ERROR);
	while (split_line[i])
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
				g_error = MALL_KO;
				return (err(ERR_MALLOC_KO), ERROR);
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
			ft_putstr_fd(1, "export ");
			ft_putstr_fd(1, tmp->name);
			ft_putstr_fd(1, "=\"");
			ft_putstr_fd(1, tmp->content);
			ft_putstr_fd(1, "\"\n");
		}
		if (tmp->name && !tmp->content)
		{
			ft_putstr_fd(1, "export ");
			ft_putstr_fd(1, tmp->name);
			ft_putstr_fd(1, "\n");
		}
		tmp = tmp->next;
	}
}

int	cmd_export(t_env **env, char *line_env)
{
	if (!*line_env)
		return (print_env_export(env), SUCCESS);
	if (add_env(env, fill_split_line(line_env)) == ERROR)
		return (ERROR);//FREE ALL---------------------------------------------------
	return (SUCCESS);
}
