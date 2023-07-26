/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:26:12 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/23 16:11:20 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		ft_pwd(void)
{
	char	cwd[4096];
	
	if (getcwd(cwd, 4096))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}