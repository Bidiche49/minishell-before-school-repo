/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:02:53 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/23 13:15:52 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define REDIR "<< < > >>"

# include <stddef.h>
# include "../minishell.h"

/*Errors*/
# define ERR_REDIR_IN_OUT "syntax error near unexpected token `newline'\n"
# define ERR_QUOTE "not handle by minishell\n"
# define ERR_MANY_ARG "too many arguments\n"
# define ERR_HOME "cd: HOME not set\n"
# define ERR_EXPORT "not a valid identifier\n"

typedef struct s_data
{
	int		nb_token;
	char	*input;
	t_token	*token;
}		t_data;

int		init_token(t_data *data, t_token *list_token);
int		is_real_command(t_token *list_token);
int		mod_input(char *input, t_data *data);
int		is_there_operator(char *input, int i, t_token *list_token);
void	init_data(char *input, t_data *data);
int		ft_error(char *error);
int		fill_tokens(t_data *data, t_token *list_token);
int		malloc_option(t_token *list_token, char *input, int i);
int		calc_i(char *input, int token_passed);

#endif
