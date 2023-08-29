/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:30:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 02:48:17 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_export(t_env **env, char *line_env)
{
	char **split_line;

	split_line = NULL;
	while (*line_env != ' ')
		line_env++;
	split_line = ft_split(line_env, ' ');
	if (!split_line)
		return (ERROR); //FREE ALL
	
}
