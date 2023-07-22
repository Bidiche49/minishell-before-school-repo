/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:56:24 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 10:33:45 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	mod_input(char *input, char *cmd_line)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while
// }

int	parsing(char *input, t_token *list_token)
{
	t_data	data;

	init_data(input, &data);
	// printf("nb token = %d\n", data.nb_token);
	if (init_token(&data, list_token) == 1)
		return (1);
	if (fill_tokens(&data, list_token) == 1)
		return (1);
	return (0);
}
