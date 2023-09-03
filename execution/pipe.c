/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:40:39 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 00:56:56 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    exec_cmd(t_section *section)
{
    char **env_tmp;

    env_tmp = ft_get_all_env(section->env);
    signal(SIGINT, &kill_child);
    signal(SIGQUIT, SIG_DFL);
    execve(section->abs_path, ft_split(section->option, ' '), env_tmp);
	free_section(section);
}

void	dispatch_cmd(t_section *section, int *pid, int *j)
{
	fork_close(section, pid, j);
	exec_cmd(section);
	exit(127);
}

void	you_pipe(int *pid, int y, t_section *section)
{
	if (pid[y] < 0)
		printf("ERROR : PIPE\n");
	if (section->abs_path)
		free(section->abs_path);
}
