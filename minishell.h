/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/05 19:08:23 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCES 0
# define ERROR 1

int        ft_strlen(const char *str);
int        ft_strcat_pars(char *abs_path, char *path, char *cmd, char sep);
int        ft_isspace(char c);
int        space_only(char *p);
char    *first_word(char *str);
char    *ft_strdup(const char *src);
char    *ft_substr(char const *s, int start, int len);
char    **ft_split(char const *s, char c);

typedef enum e_type
{
    WORD,
    S_QUOTES,
    D_QUOTES,
    SEPARATOR,
    OUT,
    IN,
    HEREDOC,
    APPEND,
    PIPE
}    t_type_token;

typedef struct s_token
{
    char    *str;
    int        type;
    struct s_token *next;
}    t_token;

/* Execution */

typedef struct s_section
{
	char	*cmd;
	char	*abs_path;
	char	*option;
	struct s_section *next;
}	t_section;

/* Execution */

void    free_all(t_token *lst_token);
int     parsing(char *input, t_token *list_token);
int     execution(t_token *token);



/* Execution */

// int	execution(t_token *token);

/* Utils_exe */

int	ft_lstsize(t_token *token);
int	ft_lstadd_back_exec(t_section **lst, t_section *new);
t_section	*ft_lstlast(t_section *lst);
void	init_list_section(t_token *token, t_section *section);

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