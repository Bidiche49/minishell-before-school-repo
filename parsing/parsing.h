/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:02:53 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/02 04:36:14 by ntardy           ###   ########.fr       */
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
# define ERR_HOME "cd: HOME not set\n"
# define ERR_EXPORT "not a valid identifier\n"

int		ft_error(char *error);
int		fill_tokens(char *input, t_token **list_token);
int		malloc_option(t_token *list_token, char *input, int i);
int		ft_strdup_remake(char *str, t_token *new);
int		is_sep_op(char c);
int		ft_lstadd_back(t_token **lst, t_token *new);
int		operator_mod(t_token *lst_token);
int		is_operator(t_token *token);
int		is_word_quote(t_token *token);
int		ft_strlen_remake(char *str);
void	free_list_token(t_token **token);
void	err_end_token(t_token *token);
t_token	*ft_newtoken(char *str);

#endif
