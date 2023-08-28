/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:07:05 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/27 11:56:11 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_token(char *input)
{
	int	i;
	int	nb_token;

	nb_token = 1;
	i = 0;
	while (input[i])
	{
		if (i > 1 && input[i - 2] != '|' && input[i - 1] == '|' && input[i] != '|')
			nb_token++;
		i++;
	}
	return (nb_token);
}

// void	init_data(char *input, t_data *data)
// {
// 	data->input = NULL;
// 	data->nb_token = count_token(input);
// 	data->token = NULL;
// }

// int malloc_token(int nb_token, t_token **list_token)
// {
// 	t_token	*tmp;

// 	tmp = *list_token;
// 	list_token = malloc(sizeof(t_token));
// 	if (list_token == NULL)
// 		return (ft_error(", malloc token KO !"));
// 	tmp->next = NULL;

// 	return (0);
// }
