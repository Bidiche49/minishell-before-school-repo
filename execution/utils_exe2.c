/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:02:37 by audrye            #+#    #+#             */
/*   Updated: 2023/08/31 12:33:58 by ntardy           ###   ########.fr       */
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
    section->abs_path = ft_calloc((len + 2), sizeof(char));
    if (!section->abs_path)
        return (malloc_error(), ERROR);
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

