/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:15:54 by augustindry       #+#    #+#             */
/*   Updated: 2023/09/07 10:20:49 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

int		is_builtin(t_section *sec);
int		exec_builtins(t_section *sec, int fd);
int		find_path(t_section *section);
int		conductor(t_section **section);
char	*ft_strjoin_path(char *s1, char *s2);
void	cmd_not_found(char *cmd);
void	free_section(t_section *section);
void	free_list_section(t_section **section);


#endif
