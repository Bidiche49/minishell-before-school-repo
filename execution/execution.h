/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:15:54 by augustindry       #+#    #+#             */
/*   Updated: 2023/09/13 06:47:58 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

typedef enum e_tab			t_tab_file;


enum e_tab{
	TMP_FD0,
	TMP_FD1,
	I,
	PREV,
	SAVE_FD0,
	SAVE_FD1
};

int		is_builtin(t_section *sec);
int		exec_builtins(t_section *sec);
int		find_path(t_section *section);
int		conductor(t_section **section);
int		openfiles(t_token *token);
int		openfiles_builtins(t_token *token);
int		contain_equal(char *line);
char	*ft_strjoin_path(char *s1, char *s2);
void	cmd_not_found(char *cmd);
void	free_section(t_section *section);
void	free_list_section(t_section **section);
void	cmd_exit(char *option);


#endif
