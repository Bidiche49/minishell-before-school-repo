/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/22 16:35:03 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

int	general_exe(t_token *token)
{
	int	i;
	int	size;

	i = 0;
	printf("test\n");
	size = ft_lstsize(token);
	printf("valeur de size = %d\n", size);
	if (token == NULL)
		return (1);
	if (size != 1)
	{
		while (i < size)
		{
			printf("valeur de i = %d\n", i);
			execute_fork_cmd(token);
			i++;
		}
	}
	else
		ft_execute_cmd(token);
	return (0);
}

int	ft_execute_cmd(t_token *token)
{
	char	*path;
	char *const	*envp;
	char *const	*argv;
	char const	*opt;
	int		res;

	opt = token->options;
	path = token->absolut_path;
	argv = (char *const *)ft_split(opt, ' ');
	envp = NULL;
	res = execve(path, argv, envp);
	if (res == -1)
		return (1);
	return (0);
}

int	execute_fork_cmd(t_token *token)
{
	int	pid;
	int	p_fd[2];

	if (pipe(p_fd) == -1)
		return(perror("pipe"), 1);
	pid = (int)fork();
	if (pid < 0)
		return(perror("fork"), 1);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		ft_execute_cmd(token);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
	return (0);
}
