/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:15:54 by augustindry       #+#    #+#             */
/*   Updated: 2023/09/02 11:29:22 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

int		is_builtin(t_section *sec);
int		find_path(t_section **section);
int		conductor(t_section **section);
char	*ft_strjoin_path(char *s1, char *s2);
void	cmd_not_found(char *cmd);
void	free_section(t_section *section);
void	free_list_section(t_section **section);


#endif
