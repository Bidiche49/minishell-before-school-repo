/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/28 22:44:48 by audrye           ###   ########.fr       */
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

void    free_all(t_token *lst_token);
int        parsing(char *input, t_token *list_token);
int        general_exe(t_token *token);

#endif