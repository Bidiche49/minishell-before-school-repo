/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:13:19 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/02 04:39:12 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../minishell.h"

# define ERR_END_TOKEN "syntax error near unexpected token `"

/******************************************/
/*               Fonctions                */
/******************************************/

/*********************************/
/*            expand             */
/*********************************/
int		special_case_expand(t_token **token);

/*********************************/
/*         expand_utils          */
/*********************************/
int		is_op(t_token *token);
int		cat_word(t_token *token);
int		is_type_wq(t_token *token);
int		is_sep_pipe(t_token *token);
int		is_in_env(char *env_var, t_env *env);
void	err_end_token(t_token *token);

/*********************************/
/*          expand_word          */
/*********************************/
int		expand_word(t_token **token, t_env **env);
int		expand_to_token(t_token **list_token, t_env **env);

/*********************************/
/*         expand_dquotes        */
/*********************************/
int		copy_var_env(char *dest, char *str, t_env *env);
int		expand_d_quotes(t_token **list_token, t_env *env);
char	*dup_dquotes(int len_tot, char *str, t_env *env);
void	fill_dquote(char *str, t_env *env, char *d_quotes);

/*********************************/
/*     expand_dquotes_utils      */
/*********************************/
int		count_len_var_name(char *str);
int		calc_len_tot(char *str, t_env *env);
int		count_len_var_content(char *str, t_env *env);

/*********************************/
/*        check_is_expand        */
/*********************************/
int		isexpand_ok(t_token *list_token);
int		is_an_exp_dquotes(t_token *list_token);

/*********************************/
/*        is_token_clean         */
/*********************************/
int		is_token_ok(t_token *tok);
int		first_tok_null(t_token *tok);

/*********************************/
/*          clean_token          */
/*********************************/
int		dble_op(t_token *tok);
int		clean_token(t_token **token);
void	del_next_token(t_token **token);

#endif
