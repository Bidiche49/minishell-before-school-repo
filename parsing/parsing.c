/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:56:24 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/23 00:00:08 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ' || c == '\0')
		return (1);
	else
		return (0);
}

int	space_only(char *p)
{
	char	*char_ptr;

	char_ptr = p;
	if (char_ptr != NULL)
	{
		while (*char_ptr)
		{
			if (ft_isspace(*char_ptr))
				char_ptr++;
			else
				return (0);
		}
		return (1);
	}
	else
		return (1);
}

int	malloc_new_input(char *input, t_data *data)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			while (ft_isspace(input[i]))
				i++;
			if (input[i] == '\0')
				break ;
		}
		len++;
		i++;
	}
	// printf("%d\n", len);
	data->input = malloc(sizeof(char) * (len + 1));
	if (data->input == NULL)
		return (ft_error(", malloc KO !"));
	return (0);
}

int	mod_input(char *input, t_data *data)
{
	int		i;
	int		j;

	if (malloc_new_input(input, data) == 1)
		return (1);
	i = 0;
	j = 0;
	while (ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			while (ft_isspace(input[i + 1]))
				i++;
			if (input[i] == '\0')
				break ;
		}
		data->input[j] = input[i];
		j++;
		i++;
	}
	data->input[j] = '\0';
	return (0);
}

int	parsing(char *input, t_token *list_token)
{
	t_data	data;

	init_data(input, &data);
	if (mod_input(input, &data) == 1)
		return (1);
	if (init_token(&data, list_token) == 1)
		return (1);
	if (fill_tokens(&data, list_token) == 1)
		return (1);
	return (0);
}
