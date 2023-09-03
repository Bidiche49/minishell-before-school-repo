/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:26:25 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 01:25:49 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_pipe(t_section *section, int x, int y)
{
	int	tmp_pipe[2];

	section->fd[0] = y;
	while (section->next)
	{
		if (pipe(tmp_pipe) > 0)
		{
			// message d'erreur = echec de la creation du pipe;
			return (-1);
		}
		section->pipe[0] = tmp_pipe[0];
		section->pipe[1] = tmp_pipe[1];
		section->fd[1] = tmp_pipe[1];
		section->next->fd[0] = tmp_pipe[0];
		section = section->next;
	}
	section->fd[1] = x;
	return (1);
}