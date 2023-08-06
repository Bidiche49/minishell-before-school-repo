/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:02:37 by audrye            #+#    #+#             */
/*   Updated: 2023/08/05 16:42:22 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	ft_strcat_token(char *path, char *cmd, t_section *section)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(path) + ft_strlen(cmd);
	section->abs_path = malloc(sizeof(char) * (len + 1));
	if (!section->abs_path)
		return (ERROR);
	while (path[i])
	{
		section->abs_path[i] = path[i];
		i++;
	}
	while (cmd[j])
	{
		section->abs_path[i] = cmd[j];
		i++;
		j++;
	}
	section->abs_path[i] = '\0';
	return (SUCCES);
}

int	ft_strcpy_token(char *src, t_section *section)
{
	int	i;

	i = 0;
	section->cmd = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!section->cmd)
		return (ERROR);
	while (src[i])
	{
		section->cmd[i] = src[i];
		i++;
	}
	section->cmd[i] = '\0';
	return (SUCCES);
}

