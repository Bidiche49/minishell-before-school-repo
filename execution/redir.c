/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:50:18 by audrye            #+#    #+#             */
/*   Updated: 2023/08/08 12:46:11 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(int type)
{
	if (type == OUT || type == IN 
		|| type == HEREDOC || type == APPEND)
		return (1);
	return (0);	
}

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