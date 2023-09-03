/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/09/02 03:09:43 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

void back_to_home(int *pid, int ret)
{
	int i;
	int status;
	int error;

	i = 0;
	while (i != ret)
	{
		if (waitpid(-1, &status, WUNTRACED) == pid[ret - 1])
		{
			if (status == 2)
				error = 130;
			else if (status > 256)
				error = status / 256;
			else
				error = status;
		}
		i++;
	}
	if (error == 130 || error == 131)
		write(1, "\n", 1);
}

void end_of_exec(int *pid, int x, int y)
{
	free(pid);
	convert_file(x, y);
	close(x);
	close(y);
}

int	orchestra_cmd(t_section *section, int *pid, int *j)
{
	int	i[2];

	i[1] = 0;
	i[0] = 1;
	while (section && i[0] > -1)
	{
		i[0] = assigne_file(section, j, i[0]);
		if (i[0] == -1)
			return (-1);
		if (i[0] == 1)
		{
			if (i[0] == -1)
				return (free(section->option), i[0]);
			if (i[0] != 0)
			{
				pid[i[1]] = fork();
				if (pid[i[1]] == 0 && i[0] == 1)
					dispatch_cmd(section, pid, j);
				you_pipe(pid, i[1]++, section);
			}
		}
		section = next_section(section, j[0], i);
	}
	return (i[1]);
}

int master_exec(t_section *section)
{
	pid_t *pid;
	int j[2];
	int ret;

	if (!section->cmd)
		return (0);
	ret = 0;
	pid = calloc(ft_lstsize_section(section), sizeof(int));
	if (!pid)
		return (0);
	pid[0] = -1;
	j[1] = dup(1);
	j[0] = dup(0);
	if (init_pipe(section, j[1], j[0]) == -1)
		return (close(j[1]), close(j[0]), -1);
	signal(SIGINT, SIG_IGN);
	ret = orchestra_cmd(section, pid, j);
	if (ret == -1)
		return (close(j[1]), close(j[0]), free(pid), -1);
	if (pid[0] != -1)
		back_to_home(pid, ret);
	return (end_of_exec(pid, j[0], j[1]), 1);
}

int execution(t_token *token, t_env **env)
{
	t_section *list_section;
	t_token	*token_tmp;

	token_tmp = token;
	list_section = NULL;
	init_section(token_tmp, &list_section, env);
	find_path(list_section);
	if (master_exec(list_section) == -1)
		return (ERROR);
	// print_section(list_section);
	return (SUCCESS);
}
