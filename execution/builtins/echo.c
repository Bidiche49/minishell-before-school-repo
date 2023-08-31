/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:32:57 by audrye            #+#    #+#             */
/*   Updated: 2023/08/31 12:26:15 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_op_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	ft_echo(t_section *section)
{
	int	i;

	i = 0;
	while (section->option[i] && section->option[i] != ' ')
		i++;
	i++;
	printf(" option = %s\n", section->option);
	while (section->option[i] && !is_op_char(section->option[i]))
		write(1, &section->option[i++], 1);
	write(1, "\n", 1);
}
