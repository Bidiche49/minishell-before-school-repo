/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:15:54 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/23 16:55:32 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <stdlib.h>
# include <errno.h>
# include <limits.h>

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_mini
{
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
	t_env			*env;
	t_env			*env_s;
}				t_mini;

int	general_exe(t_token *token);
int	ft_execute_cmd(t_token *token);
int	execute_fork_cmd(t_token *token);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

char	**ft_split(char const *s, char c);
// static char	**ft_empty_malloc(void);
// static void	*ft_free(char **s, int j);
// static int	ft_size(char const *s, char c, int i);
// static int	ft_count(char const *s, char c);
char	*ft_substr(char const *s, int start, int len);
int ft_strlen(const char *str);

int	ft_lstsize(t_token *lst);

#endif
