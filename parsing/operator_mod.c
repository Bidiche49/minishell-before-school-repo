/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 00:23:12 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 04:27:26 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	del_word_sep(t_token *operator, t_token *opt)
{
	t_token	*tmp;

	tmp = opt->next;
	if (operator->next->type == SEPARATOR)
	{
		tracked_free(operator->next);
		tracked_free(opt->str);
		tracked_free(opt);
	}
	else
	{
		tracked_free(opt->str);
		tracked_free(opt);
	}
	operator->next = tmp;
}

int	operator_mod(t_token *lst_token)
{
	t_token	*operator;
	t_token	*opt;

	operator = lst_token;
	while(operator->next)
	{
		if (is_operator(operator))
		{
			opt = operator;
			if (is_word_quote(opt->next))
				opt = opt->next;
			else if (opt->next->type == SEPARATOR && is_word_quote(opt->next->next))
				opt = opt->next->next;
			if (is_word_quote(opt))
			{
				operator->str = ft_strdup(opt->str);
				if (operator->str == NULL)
					return (ERROR); // malloc error
				del_word_sep(operator, opt);
			}
		}
		operator = operator->next;
		if(!operator)
			return (SUCCESS);
	}
	return (SUCCESS);
}
