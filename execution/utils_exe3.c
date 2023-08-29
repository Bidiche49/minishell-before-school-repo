/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 01:03:58 by audrye            #+#    #+#             */
/*   Updated: 2023/08/29 04:34:13 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

void	add_space(t_section *section)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(section->option) + 2));
	while (section->option[i])
	{
		tmp[i] = section->option[i];
		i++;
	}
	free(section->option);
	tmp[i] = ' ';
	tmp[i + 1] = '\0';
	section->option = tmp;
}

int	is_pipe(t_section *section)
{
	int	i;
	
	i = 0;
	while (section)
	{
		i++;
		section = section->next;
	}
	return (i);
}