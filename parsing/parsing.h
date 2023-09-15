/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:02:53 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/15 18:36:15 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

/******************************************/
/*                Defines                 */
/******************************************/
# define ERR_REDIR_IN_OUT "syntax error near unexpected token `newline'\n"
# define ERR_QUOTE "not handle by minishell\n"
# define ERR_HOME "cd: HOME not set\n"
# define ERR_EXPORT "not a valid identifier\n"

/******************************************/
/*               Fonctions                */
/******************************************/

/*********************************/
/*             fill              */
/*********************************/
int		fill_tokens(char *input, t_token **list_token);
int		ft_strdup_remake(char *str, t_token *new);
t_token	*ft_newtoken(char *str);

/*********************************/
/*         operator_mod          */
/*********************************/
int		operator_mod(t_token *lst_token);

/*********************************/
/*          pars_utils           */
/*********************************/
int		is_sep_op(char c);
int		ft_isspecial(char c);
int		is_operator(t_token *token);
int		is_word_quote(t_token *token);

/*********************************/
/*       ft_strlen_remake        */
/*********************************/
int		ft_strlen_remake(char *str);
int		ft_strlen_word(char *str);
int		ft_strlen_quotes(char *str);

#endif
