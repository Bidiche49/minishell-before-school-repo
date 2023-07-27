/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:31:21 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/27 12:30:05 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	fill_tokens(char *input, t_token *list_token)
{
	char	*tmp_input;

	tmp_input = input;
	while (*tmp_input)
	{
		if (ft_lstadd_back(&list_token, ft_newtoken(tmp_input)) == 1)
				return (free_list_token(list_token), 1);
		while (*tmp_input && !ft_isspace(*tmp_input))
			tmp_input++;
	}
	return (0);
}

// int	fill_command(t_data *data, t_token *list_token, int i)
// {
// 	list_token->cmd = first_word(&data->input[i]);
// 	if (list_token->cmd == NULL)
// 		return (ft_error(", malloc error !"));
// 	if (is_real_command(list_token) == 1)
// 		return (1);
// 	return (0);
// }

// int	fill_tokens(t_data *data, t_token *list_token)
// {
// 	int		i;
// 	int		token_passed;
// 	t_token *tmp;

// 	i = 0;
// 	token_passed = 0;
// 	tmp = list_token;
// 	while (list_token)
// 	{
// 		while (data->input[i] && ft_isspace(data->input[i]))
// 			i++;
// 		fill_command(data, list_token, i);
// 		i = is_there_operator(data->input, i, list_token);
// 		if (i == -1)
// 			return (1);
// 		if (fill_option(data->input, list_token, token_passed) == 1)
// 			return (1);
// 		token_passed++;
// 		list_token = list_token->next;
// 	}
// 	list_token = tmp;
// 	return (0);
// }
