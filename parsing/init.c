/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:07:05 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 23:10:33 by ntardy           ###   ########.fr       */
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

void	init_data(char *input, t_data *data)
{
	data->input = NULL;
	data->nb_token = count_token(input);
	data->token = NULL;
}

int malloc_token(int nb_token, t_token **list_token)
{
	t_token	*tmp;

	tmp = *list_token;
	list_token = malloc(sizeof(t_token));
	if (list_token == NULL)
		return (ft_error(", malloc token KO !"));
	tmp->next = NULL;
	while (--nb_token > 0)
	{
		tmp->next = malloc(sizeof(t_token));
		if (tmp->next == NULL)
			return (ft_error(", malloc token KO !"));
		tmp = tmp->next;
		tmp->next = NULL;
	}
	return (0);
}

int	init_token(t_data *data, t_token *list_token)
{
	t_token *tmp;

	if (malloc_token(data->nb_token, &list_token) != 0)
		return (1);
	tmp = list_token;
	while (list_token)
	{
		list_token->cmd = NULL;
		list_token->absolut_path = NULL;
		list_token->options = NULL;
		list_token->redir = NULL;
		list_token->operateur = NULL;
		list_token = list_token->next;
	}
	list_token = tmp;
	return (0);
}

