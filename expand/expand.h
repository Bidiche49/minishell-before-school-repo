/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:13:19 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/29 07:04:55 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../minishell.h"

int		is_in_env(char *env_var, t_env *env);
int		isexpand_ok(t_token *list_token);
int		is_an_exp_dquotes(t_token *list_token);
int		expand_d_quotes(t_token **list_token, t_env *env);
int		expand_word(t_token **token, t_env **env);
int		expand_to_token(t_token **list_token);
int		special_case_expand(t_token **token);
int		copy_var_env(char *dest, char *str, t_env *env);
int		count_len_var_content(char *str, t_env *env);
int		count_len_var_name(char *str);
int		is_op(t_token *token);
int		calc_len_tot(char *str, t_env *env);
char	*dup_dquotes(int len_tot, char *str, t_env *env);
void	fill_dquote(char *str, t_env *env, char *d_quotes);
void	del_next_token(t_token **token);

#endif
