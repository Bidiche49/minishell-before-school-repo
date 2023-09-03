/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:55:26 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 11:09:37 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_get_env(t_env **env, char *str)
{
	char *res;
	t_env *tmp;
	int i;
	int j;

	j = 0;
	tmp = *env;
	i = ft_strlen(tmp->name) + ft_strlen(tmp->content);
	while (tmp && ft_strcmp(tmp->name, str) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	res = ft_calloc((i + 2), sizeof(char));
	if (!res)
		return (NULL);
	while (tmp->name[j++])
		res[j] = tmp->name[j];
	i = 0;
	res[j] = '=';
	while (tmp->content[i])
		res[j++] = tmp->content[i++];
	return (res);
}

int	ft_lstsize_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	*cpy_new_line(char *tmp, char *s1, char *s2)
{
	int	i;
	int j;
	
	i = 0;
	j = 0;
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i++] = '=';
	while (s2[j])
	{
		tmp[i] = s2[j];
		i++;
		j++;
	}
	return (tmp);
}

char	**ft_get_all_env(t_env	**env)
{
	char	**env_tmp;
	t_env	*tmp;
	int		i;
	int		size;

	i = 0;
	tmp = *env;
	env_tmp = ft_calloc((ft_lstsize_env(*env) + 1), sizeof(char *));
	if (!env_tmp)
		return(NULL); //FREEEEEALLALALALALAL
	tmp = *env;
	while (tmp)
	{
		size = ft_strlen(tmp->name) + ft_strlen(tmp->content);
		env_tmp[i] = ft_calloc((size + 3), sizeof(char));
		if (!env_tmp[i])
			return (NULL); //FREE ALLLLLLL
		env_tmp[i] = cpy_new_line(env_tmp[i], tmp->name, tmp->content);
		i++;
		tmp = tmp->next;
	}
	return (env_tmp);
}
