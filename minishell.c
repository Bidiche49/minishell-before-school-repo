/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 18:40:28 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_error;

int	main_loop(char *input, t_token **token, t_env **env)
{
	int	return_val;

	config_minishell_signal();
	while (1)
	{
		input = readline("\001" BOLD CYAN "\002" "Minishell > " "\001" RESET "\002");
		if (!input)
			break ;
		else if (ft_strlen(input) > 0 && !space_only(input))
		{
			add_history(input);
			return_val = parsing(input, token, env);
			if (return_val == ERROR)
				return (ERROR);
			if (return_val == SUCCESS)
				if (execution(*token, env) == ERROR)
					return (ERROR);
		}
	}
	return (SUCCESS);
}

int	end_funct()
{
	close(0);
	close(1);
	close(2);
	garbage_collect();
	rl_clear_history();
	printf(BOLD GREEN "exit\n" RESET);
	return (g_error);
}

int	main(int argc, char **argv, char **envd)
{
	char			*input;
	t_token			*token;
	static t_env	*env = NULL;

	input = NULL;
	token = NULL;
	if (argc != 1)
		return (msg(ERR_MANY_ARG), ERROR);
	if (create_env(envd, &env) == ERROR)
		return (garbage_collect(), rl_clear_history(), g_error);
	if (main_loop(input, &token, &env) == ERROR)
		return (garbage_collect(), rl_clear_history(), g_error);
	return ((void)argv, end_funct());
}
