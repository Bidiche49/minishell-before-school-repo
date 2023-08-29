/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:32:57 by audrye            #+#    #+#             */
/*   Updated: 2023/08/29 15:19:49 by audrye           ###   ########.fr       */
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
	while (section->option[i] && !is_op_char(section->option[i]))
		write(1, &section->option[i++], 1);
	write(1, "\n", 1);
}
