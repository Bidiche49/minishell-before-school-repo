/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:46:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 01:04:44 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

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
	while (line_env && *line_env && *line_env != '=')
		new->name[i++] = *line_env++;
	new->name[i] = '\0';
	i = 0;
	new->content = malloc(sizeof(char) * (ft_strlen_char(line_env, '\0') + 1));
	if (!new->content)
		return (NULL);
	while (line_env && *++line_env)
		new->content[i++] = *line_env;
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
