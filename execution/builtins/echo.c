/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:32:57 by audrye            #+#    #+#             */
/*   Updated: 2023/09/12 23:41:54 by ntardy           ###   ########.fr       */
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
	if (!section->option)
		return ;
	while (section->option[i] && section->option[i] != ' ')
		i++;
	if (section->option[i])
		i++;
	while (section->option[i] && !is_op_char(section->option[i]))
		write(STDOUT_FILENO, &section->option[i++], 1);
	write(STDOUT_FILENO, "\n", 1);
}
