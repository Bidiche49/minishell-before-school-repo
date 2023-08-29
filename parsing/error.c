/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:00 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 05:42:11 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	err_end_token(t_token *token)
{

	if (token->type	== PIPE)
		printf("%s|'\n", ERR_END_TOKEN);
	if (token->type	== IN)
		printf("%s<'\n", ERR_END_TOKEN);
	if (token->type	== OUT)
		printf("%s>'\n", ERR_END_TOKEN);
	if (token->type	== APPEND)
		printf("%s>>'\n", ERR_END_TOKEN);
	if (token->type	== HEREDOC)
		printf("%s<<'\n", ERR_END_TOKEN);
	g_error = 2;
}
