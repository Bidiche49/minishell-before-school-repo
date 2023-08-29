/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:45:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 09:58:31 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_env_line(t_env **actual)
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

int	del_var_env(t_env **env, char *line)
{
	t_env	*tmp;

	tmp = *env;
	if (!line || !line[0])
		return (0);
	if (line[0] == '\"')
		line++;
	while (*line == ' ')
		line++;
	while (tmp->next)
	{
		if (tmp->next && (ft_strncmp(line, tmp->next->content, ft_strlen_char(line, ' '))
			|| ft_strncmp(line, tmp->next->content, ft_strlen_char(line, '\"'))))
			del_env_line(&tmp);
		tmp = tmp->next;
	}
	if (ft_strlen_char(line, ' ') < ft_strlen_char(line, '\"'))
		return (ft_strlen_char(line, ' ') + 1);
	else
		return (ft_strlen_char(line, '\"') + 1);
}

void	cmd_unset(t_env **env, char *line_env)
{
	int	i;

	i = 0;
	if (!line_env)
		return ;
	while (line_env[i] && line_env[i + 1] && line_env[i + 1] != ' ')
		i++;
	while (line_env[i])
	{
		while(line_env[i] && line_env[i] == ' ')
			i++;
		i += del_var_env(env, line_env + i);
		while (line_env[i] && line_env[i] == '\"')
			i++;
	}
}
