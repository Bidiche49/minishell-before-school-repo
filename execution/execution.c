/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/22 11:27:09 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include <stddef.h>
#include <unistd.h>



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
		return (/*error dans l'execution*/ 1);
	return (0);
}
