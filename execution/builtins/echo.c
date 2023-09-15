/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:32:57 by audrye            #+#    #+#             */
/*   Updated: 2023/09/14 23:46:55 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_op_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	ft_echo(char *opt)
{
	int	i;
	int	n;

	n = 1;
	i = 0;
	if (!opt)
		return ;
	while (opt[i] && opt[i] != ' ')
		i++;
	if (opt[i] == ' ')
		i++;
	if (opt[i] && opt[i] == '-' && opt[i + 1] && opt[i + 1] == 'n')
	{
		if (opt[i + 2] && opt[i + 2] == ' ')
			i += 3;
		if (opt[i])
		{
			i += 1;
			while(opt[i] == 'n')
				i++;
			if (opt[i] && opt[i] == ' ')
				i++;
		}
		else
			return ;
		n = 0;
	}
	while (opt[i] && !is_op_char(opt[i]))
		write(STDOUT_FILENO, &opt[i++], 1);
	if (n)
		write(STDOUT_FILENO, "\n", 1);
}
