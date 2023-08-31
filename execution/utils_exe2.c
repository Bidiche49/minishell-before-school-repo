/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:02:37 by audrye            #+#    #+#             */
/*   Updated: 2023/08/31 02:17:43 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int    ft_strcat_token(char *path, char *cmd, t_section *section)
{
    int    i;
    int    j;
    int    len;

    i = 0;
    j = 0;
    len = ft_strlen(path) + ft_strlen(cmd);
    free(section->abs_path);
    section->abs_path = malloc(sizeof(char) * (len + 2));
    if (!section->abs_path)
        return (ERROR);
    while (path[i])
    {
        section->abs_path[i] = path[i];
        i++;
    }
    section->abs_path[i++] = '/';
    while (cmd[j])
    {
        section->abs_path[i] = cmd[j];
        i++;
        j++;
    }
    section->abs_path[i] = '\0';
    return (SUCCESS);
}

int	ft_lstsize(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

