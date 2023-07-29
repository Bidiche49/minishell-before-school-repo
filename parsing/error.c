/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:00 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/28 16:31:28 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_error(char *error)
{
	write(2, "Error", 5);
	if (error)
		write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (ERROR);
}
