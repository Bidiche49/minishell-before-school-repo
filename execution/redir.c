/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:50:18 by audrye            #+#    #+#             */
/*   Updated: 2023/08/30 21:42:54 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator_exec(t_token *token)
{
	while (token)
	{
		if (token->type == OUT || token->type == IN || token->type == HEREDOC
			|| token->type == APPEND || token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}