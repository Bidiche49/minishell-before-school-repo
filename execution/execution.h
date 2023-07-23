/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:15:54 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/23 13:16:02 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <stdlib.h>

int	general_exe(t_token *token);
int	ft_execute_cmd(t_token *token);
int	execute_fork_cmd(t_token *token);
// static char	**ft_empty_malloc(void);
// static void	*ft_free(char **s, int j);
// static int	ft_size(char const *s, char c, int i);
// static int	ft_count(char const *s, char c);
char	*ft_substr(char const *s, int start, int len);
int ft_strlen(const char *str);

int	ft_lstsize(t_token *lst);

#endif
