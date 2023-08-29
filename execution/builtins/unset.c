/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:45:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 21:57:44 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	de_env_var(t_env **actual)
{
	t_env	*tmp2;

	tmp2 = (*actual)->next->next;
	if ((*actual)->next->name)
		free((*actual)->next->name);
	if ((*actual)->next->content)
		free((*actual)->next->content);
	free((*actual)->next);
	(*actual)->next = tmp2;
}

void	del_first_env_var(t_env **lst)
{
	t_env	*tmp2;

	tmp2 = (*lst)->next;
	if ((*lst)->name)
		free((*lst)->name);
	if ((*lst)->content)
		free((*lst)->content);
	free((*lst));
	(*lst) = tmp2;
}

int	del_var_env(t_env **env, char *line)
{
	t_env	*tmp;
	int		len_name;
	char	*name;

	if (!line || !line[0])
		return (0);
	if (*line == ' ')
		line++;
	tmp = *env;
	len_name = ft_strlen_char(line, '=');
	name = line;
	name[len_name] = '\0';
	if ((!ft_strcmp(name, (*env)->name)))
			return (del_first_env_var(env), ft_strlen_char(line, ' ') + 1);
	while (tmp)
	{
		// printf("%s ?= %s\n",tmp->next->name, line);
		if (tmp->next && (!ft_strcmp(name, tmp->next->name)))
			return (de_env_var(&tmp), ft_strlen_char(line, ' ') + 1);
		tmp = tmp->next;
	}
	return (ft_strlen_char(line, ' ') + 1);
}

int	pass_cmd(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] && line[i] == ' ')
		i++;
	return (i);
}

void	cmd_unset(t_env **env, char *line_env)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	(void)quotes;
	if (!line_env)
		return ;
	i = pass_cmd(line_env);
	// if (line_env[i] && (line_env[i] != '"' || line_env[i] == '\''))
	// {
	// 	quotes = 1;
	// 	i++;
	// }
	// printf("c = |%c|\n", line_env[i]);
	while (line_env[i])
	{
		// if (line_env[i] && line_env[i] == ' ')
		// 	i++;
		i += del_var_env(env, line_env + i);
		// while (line_env[i] && line_env[i] == '"')
		// 	i++;
	}
}
