/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_section.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:04:45 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 00:08:06 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_section(t_section *section)
{
	if (section->cmd)
		free(section->cmd);
	if (section->abs_path)
		free(section->abs_path);
	if (section->option)
		free(section->option);
	// fermer les fd
	free(section);
	section = NULL;
}

void	free_list_section(t_section **section)
{
	t_section *tmp;
	
	if (!section)
		return ;
	while (section)
	{
		tmp =(*section);
		while (tmp->next)
			tmp = tmp->next;
		free_section(tmp);	
	}
	free(section);
}