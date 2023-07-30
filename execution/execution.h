/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:15:54 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/30 01:51:08 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_section
{
	char	*cmd;
	char	*abs_path;
	char	*option;
	struct t_section *next;
}	t_section;

/* Execution */

int	execution(t_token *token);

/* Utils_exe */

int	ft_lstsize(t_token *lst);
void	ft_lstadd_back(t_section **lst, t_section *new);
t_section	*ft_lstlast(t_section *lst);

/* Utils_exe2 */

int	ft_strcat_token(char *path, char *cmd, t_section *section);
int	ft_strcpy_token(char *src, t_section *section);

/* Utils_exe3 */

int	ft_strcat_exec_sec(t_section *section, char *exec);
int	ft_strcat_exec_sec_s(t_section *section, char *exec);
int	ft_strcpy_exec_s(char *src, t_section *section);
int	ft_strcpy_exec_d(char *src, t_section *section);
int	is_meta_c(char *simple_c);
char	*add_space(char *section);

/* Utils_exe3 */

int	is_meta_d(char *simple_d);
int	ft_strcat_exec_sec_d(t_section *section, char *exec);
int	is_back(char *str);

#endif
