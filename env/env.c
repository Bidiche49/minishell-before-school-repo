/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:46:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/09 19:58:14 by ntardy           ###   ########.fr       */
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
	int		len_name;
	char	is_equals;
	char	*name;

	len_name = ft_strlen_char(line_env, '=');
	name = line_env;
	is_equals = name[len_name];
	name[len_name] = '\0';
	new = malloc(sizeof(t_env));
	if (!new)
		return (malloc_error(), NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return(malloc_error(), free_new_env(new), NULL);
	if (!is_equals)
		return (new->content = NULL, new->next = NULL, new);
	new->content = ft_strdup(line_env + len_name + 1);
	if (!new->content)
		return (malloc_error(), free_new_env(new), NULL);
	new->next = NULL;
	return (line_env[len_name] = is_equals, new);
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
