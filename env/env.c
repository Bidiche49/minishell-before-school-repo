/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:46:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 09:53:47 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_new_env(t_env *env)
{
	if (!env)
		return ;
	if (env->name)
		free(env->name);
	if (env->content)
		free(env->content);
	free(env);
}

t_env	*fill_new_env(char *line_env)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env *));
	if (!new)
		return (NULL);
	new->name = malloc(sizeof(char) * (ft_strlen_char(line_env, '=') + 1));
	if (!new->name)
		return (free(new), NULL);
	if (*line_env == '\"')
		line_env++;
	while (line_env && *line_env && *line_env != '=')
	{
		if (*line_env == '\"' && (!*line_env + 1 || *line_env + 1 == '='))
			break ;
		if (*line_env == '\"')
			line_env++;
		new->name[i++] = *line_env++;
	}
	new->name[i] = '\0';
	i = 0;
	if (*line_env != '=')
		return (new->content = NULL, new->next = NULL, new);
	if (*line_env + 1 && *line_env + 1 == ' ')
		line_env[1] = '\0';
	if (*line_env + 1 && *line_env + 1 == '\"')
		line_env++;
	new->content = malloc(sizeof(char) * (ft_strlen_char(line_env, '\0') + 1));
	if (!new->content)
		return (free_new_env(new), NULL);
	while (line_env && *++line_env)
	{
		if (line_env[i] == '\"')
			break ;
		new->content[i++] = *line_env;
	}
	new->content[i] = '\0';
	new->next = NULL;
	return (new);
}

int	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*actu;

	if (new == NULL)
		return (ERROR);
	if (*lst == NULL)
	{
		*lst = new;
		return (SUCCESS);
	}
	actu = *lst;
	while (actu->next != NULL)
		actu = actu->next;
	actu->next = new;
	return (SUCCESS);
}

int	create_env(char **envd, t_env **env)
{
	int	i;

	i = 0;
	while (envd[i])
	{
		if (ft_lstadd_back_env(env, fill_new_env(envd[i])))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
