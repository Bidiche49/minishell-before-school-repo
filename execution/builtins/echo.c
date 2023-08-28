/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:32:57 by audrye            #+#    #+#             */
/*   Updated: 2023/08/28 08:37:59 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_section *section)
{
	int	i;

	printf("salut\n");
	i = 0;
	while (section->option[i] && section->option[i] != ' ')	
		i++;
	while (section->option[i] && section->option[i] != ' ')
		write(1, &section->option[i++], 1);
}