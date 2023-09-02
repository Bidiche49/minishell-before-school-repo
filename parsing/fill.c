/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:31:21 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/02 06:21:00 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*find_next_quote(char *str, char c)
{
	if (*str == c)
	{
		str++;
		while (*str && *str != c)
			str++;
		str++;
		return (str);
	}
	return (NULL);
}

char	*pass_word(char *str)
{
	if (*str == '>' && *(str + 1) && *(str + 1) == '>')
		return (str + 2);
	if (*str == '<' && *(str + 1) && *(str + 1) == '<')
		return (str + 2);
	if (*str == '<')
		return (str + 1);
	if (*str == '>')
		return (str + 1);
	if (*str == '|')
		return (str + 1);
	if (find_next_quote(str, '"'))
		return (find_next_quote(str, '"'));
	if (find_next_quote(str, '\''))
		return (find_next_quote(str, '\''));
	return (NULL);
}

char	*next_token(char *str)
{
	if (ft_isspace(*str))
	{
		while (*str && ft_isspace(*str))
			str++;
		return (str);
	}
	if (pass_word(str))
		return (pass_word(str));
	if (*str == '$')
	{
		str++;
		if (*str == '$')
			return (++str);
		while (*str && !is_sep_op(*str))
			str++;
		return (str);
	}
	else
	{
		while (*str && !is_sep_op(*str))
			str++;
		return (str);
	}
}

int fill_tokens(char *input, t_token **list_token)
{
	char	*tmp_input;
	t_token	*new_token;

	tmp_input = input;
	while (*tmp_input && ft_isspace(*tmp_input))
		tmp_input++;
	while (*tmp_input)
	{
		new_token = ft_newtoken(tmp_input);
		if (ft_strlen_remake(tmp_input) == -1)
			return (write(0, ERR_QUOTES_OPEN, ft_strlen(ERR_QUOTES_OPEN)), NEW_LINE);
		if (ft_lstadd_back(list_token, new_token) == ERROR)
			return (ERROR);
		printf("tsest\n");
		tmp_input = next_token(tmp_input);
	}
	print_token(*list_token);
	return (SUCCESS);
}
