/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/30 02:06:42 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define ERROR 1
# define NEW_LINE 2
# define ERR_MANY_ARG "too many arguments\n"

extern int				g_error;

typedef enum e_type		t_type_token;
typedef struct s_token	t_token;

enum e_type{
	WORD,
	S_QUOTES,
	D_QUOTES,
	SEPARATOR,
	OUT,
	IN,
	HEREDOC,
	APPEND,
	PIPE
};

struct s_token{
	char	*str;
	int		type;
	t_token	*next;
};

int		ft_strlen(const char *str);
int		ft_strcat_pars(char *abs_path, char *path, char *cmd, char sep);
int		ft_isspace(char c);
int		space_only(char *p);
char	*first_word(char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, int start, int len);
char	**ft_split(char const *s, char c);
void	free_all(t_token *lst_token);
int		parsing(char *input, t_token **list_token);
int		general_exe(t_token *token);
void	config_minishell_signal(void);
void	free_list_token(t_token **lst_token);
void	print_token(t_token *list_token);

#endif
