/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:13:19 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 00:00:02 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../minishell.h"

int		ft_strlen_char(char *str, char c);
int		is_in_env(char *env_var, t_env *env);
int		is_num(char c);
int		is_alnum_und(char c);
int		isexpand_ok(t_token *list_token);
void	del_next_token(t_token **token);
int		is_an_exp_dquotes(t_token *list_token);

#endif
