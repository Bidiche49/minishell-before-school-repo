/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:15:54 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/22 15:58:03 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <stdlib.h>

int	general_exe(t_token *token);
int	ft_execute_cmd(t_token *token);
int	execute_fork_cmd(t_token *token);

char	**ft_split(char const *s, char c);
static char	**ft_empty_malloc(void);
static void	*ft_free(char **s, int j);
static int	ft_size(char const *s, char c, int i);
static int	ft_count(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int ft_strlen(const char *str);

int	ft_lstsize(t_token *lst);

#endif