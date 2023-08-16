/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:00 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/29 18:23:46 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_error(char *error)
{
	write(2, "Error", 5);
	if (error)
		write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (ERROR);
}

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
}
