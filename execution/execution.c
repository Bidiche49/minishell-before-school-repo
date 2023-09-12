/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 06:23:22 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/11 23:28:52 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void print_section(t_section *section)
{
	while (section)
	{
		if (section->cmd)
			printf("%s\n", section->cmd);
		if (section->abs_path)
			printf("%s\n", section->abs_path);
		if (section->option)
			printf("%s\n", section->option);
		printf("%d\t%d\n", section->fd[0], section->fd[1]);
		printf("%d\t%d\n", section->pipe[0], section->pipe[1]);
		printf("%d\n", section->deep);
		// cmd_env(section->env);
		print_token(section->token);
		section = section->next;
	}
}

int	execution(t_token *token, t_env **env)
{
	t_section	*section;
	int			return_val;

	section = NULL;
	if (init_section(token, &section, env) == ERROR)
		return (free_list_section(&section), ERROR);
	return_val = conductor(&section);
	if (return_val != SUCCESS)
		return (free_list_section(&section), return_val);
	(void)return_val;
	return (free_list_section(&section), SUCCESS);
}
