/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 06:37:12 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 21:05:52 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	option_is_digit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (!is_num(str[i]))
			return (0);
	return (1);
}

void	clean_prg(void)
{
	garbage_collect();
	close(0);
	close(1);
	close(2);
	rl_clear_history();
}

void	cmd_exit(char *option)
{
	printf(BOLD GREEN "exit\n" RESET);
	if (option)
	{
		while (*option && *option != ' ')
			option++;
		if (*option == ' ')
			option++;
		if (ft_countword(option, ' ') > 1)
			return (g_error = 1, msg("minishell: exit: too many arguments\n"));
		else if (!option_is_digit(option))
		{
			msg("minishell: exit: ");
			msg(option);
			msg(": numeric argument required\n");
			g_error = 2;
		}
		if (option_is_digit(option))
			g_error = ft_atoi(option);
	}
	return (clean_prg(), exit(g_error));
}
