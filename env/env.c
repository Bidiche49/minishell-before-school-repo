/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:46:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 23:27:02 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_new_env(t_env *env)
{
	if (!env)
		return ;
	if (env->name)
		tracked_free(env->name);
	if (env->content)
		tracked_free(env->content);
	tracked_free(env);
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
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (tracked_free(new), NULL);
	if (!is_equals)
		return (new->content = NULL, new->next = NULL, new);
	new->content = ft_strdup(line_env + len_name + 1);
	if (!new->content)
		return (free_new_env(new), NULL);
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
	int		i;
	char	*str;

	i = 0;
	if (!envd[0])
	{
		str = ft_strdup("PATH=/bin");
		if (ft_lstadd_back_env(env, fill_new_env(str)) == ERROR)
			return (ERROR);
		tracked_free(str);
		str = ft_strdup("SHLVL=1");
		if (ft_lstadd_back_env(env, fill_new_env(str)) == ERROR)
			return (ERROR);
		tracked_free(str);
		return (SUCCESS);
	}
	while (envd[i])
	{
		if (ft_lstadd_back_env(env, fill_new_env(envd[i])))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
