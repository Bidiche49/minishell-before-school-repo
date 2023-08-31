/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 01:03:58 by audrye            #+#    #+#             */
/*   Updated: 2023/08/30 21:46:28 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	ft_lstsize_section(t_section *section)
{
	int	i;
	
	i = 0;
	while (section)
	{
		i++;
		section = section->next;
	}
	return (i);
}
