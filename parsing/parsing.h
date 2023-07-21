/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:02:53 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/21 22:36:11 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define REDIR "<< < > >>"

# include <stddef.h>
# include "../minishell.h"

typedef struct s_data
{
	int		nb_token;
	char	*input;
	t_token	*token;
}		t_data;

int		init_token(t_data *data, t_token *list_token);
void	init_data(char *input, t_data *data);
int		ft_error(char *error);
int		fill_tokens(t_data *data, t_token *list_token);
char	**ft_split_pars(char const *s, char c);

#endif
