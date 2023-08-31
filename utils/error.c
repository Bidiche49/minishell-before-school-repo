/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 03:40:08 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/31 10:47:40 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msg(char *str)
{
	int	i;

	i = 0;
	i = ft_strlen(str);
	write(STDERR_FILENO, str, i);
}

void	malloc_error(void)
{
	g_error = MALL_KO;
	msg(ERR_MALLOC_KO);
}
