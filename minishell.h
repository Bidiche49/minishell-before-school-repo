/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/09/16 00:12:00 by ntardy           ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

/******************************************/
/*                Defines                 */
/******************************************/

/*********************************/
/*            colors             */
/*********************************/
# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define CYAN	"\033[36m"
# define BOLD	"\033[1m"

/*********************************/
/*         return_code           */
/*********************************/
# define SUCCESS 0
# define ERROR 1
# define NEW_LINE 2
# define EXIT 3
# define MALL_KO 55
# define CMD_KO 127
# define FORK_KO 92

/*********************************/
/*          error_msg            */
/*********************************/
# define ERR_PERM_DENIED ": Permission denied\n"
# define ERR_FORK "minishell: init fork error\n"
# define ERR_MALLOC_KO "minishell: Error malloc\n"
# define ERR_CMD_NOT_FOUND ": command not found\n"
# define ERR_NO_FILE ": No such file or directory\n"
# define ERR_MANY_ARG "minishell: too many arguments\n"
# define ERR_QUOTES_OPEN "minishell: Error quote open\n"
# define ERR_END_TOKEN "minishell: syntax error near unexpected token `"
# define ERR_ENV_KO "minishell: Error while retrieving the environment.\n"

extern int				g_error;

/******************************************/
/*             Structures                 */
/******************************************/

/*********************************/
/*           typedef             */
/*********************************/
typedef enum e_type			t_type_token;
typedef struct s_token		t_token;
typedef struct s_garbage	t_garbage;
typedef struct s_fd_garbage	t_fd_garbage;
typedef struct s_env		t_env;
typedef struct s_section	t_section;

/*********************************/
/*          enum_type            */
/*********************************/
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

/*********************************/
/*           garbages            */
/*********************************/
struct s_garbage{
	void		*ptr;
	t_garbage	*next;
};

struct s_fd_garbage{
	int				fd;
	t_fd_garbage	*next;
};

/*********************************/
/*            token              */
/*********************************/
struct s_token{
	char	*str;
	int		type;
	t_token	*next;
};

/*********************************/
/*             env               */
/*********************************/
struct s_env{
	char	*name;
	char	*content;
	t_env	*next;
};

/*********************************/
/*           section             */
/*********************************/
struct s_section{
	char		*cmd;
	char		*abs_path;
	char		*option;
	int			fd[2];
	int			pipe[2];
	int			deep;
	t_env		**env;
	t_token		*token;
	t_section	*next;
};

/******************************************/
/*                                        */
/*              FONCTIONS                 */
/*                                        */
/******************************************/

/*********************************/
/*             env               */
/*********************************/
int		create_env(char **envd, t_env **env);
int		ft_lstadd_back_env(t_env **lst, t_env *new);
char	*ft_get_env_line(t_env	**env, char *name);
t_env	*fill_new_env(char *line_env);

/*********************************/
/*            parsing            */
/*********************************/
int		parsing(char *input, t_token **token, t_env **env);

/*********************************/
/*            expand             */
/*********************************/
int		expand(t_token **list_token, t_env **env);
int		expand_d_quotes(t_token **list_token, t_env *env);

/*********************************/
/*           execution           */
/*********************************/
int		execution(t_token *token, t_env **env);
int		init_section(t_token *token, t_section **section, t_env **env);

/*********************************/
/*             check             */
/*********************************/
int		is_num(char c);
int		is_redir(int type);
int		ft_isspace(char c);
int		space_only(char *p);
int		is_alnum_und(char c);

/*********************************/
/*             utils             */
/*********************************/
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		ft_strlen_char(char *str, char c);
int		ft_countword(char const *s, char c);
int		ft_lstadd_back(t_token **lst, t_token *new);
char	*ft_itoa(int n);
char	*first_word(char *str);
void	ft_putstr_fd(int fd, char *s);
t_token	*lst_last(t_token *lst);

/*********************************/
/*       utils_malloc_str        */
/*********************************/
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcat_dup(char *dest, char *str);
char	*ft_substr(char const *s, int start, int len);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);

/*********************************/
/*             error             */
/*********************************/
void	msg(char *str);
void	malloc_error(void);
void	err_end_token(int type);
void	cmd_not_found(char *cmd);
void	error_export(char *line);
void	err_cmd_path(char *cmd, char *err, int error);
int		error_redir(char *str, int referal);

/*********************************/
/*       garbage_collector       */
/*********************************/
int				tracked_open(char *str, int fst, int scd, int trd);
int				is_fd_open(int fd);
void			collect_fd();
void			collect_ptr();
void			garbage_collect();
void			tracked_close(int fd);
void			add_fd_garbage(int fd);
void			tracked_free(void *ptr);
t_garbage		**get_garbage(void);
t_fd_garbage	**get_fd_garbage(void);

/*********************************/
/*            signal             */
/*********************************/
void	signal_heredoc(int sig);
void	config_default_signal(void);
void	config_minishell_signal(void);

/*********************************/
/*             free              */
/*********************************/
void	free_env(t_env **env);
void	free_new_env(t_env *env);
void	free_matrice(char **matrice);
void	free_list_token(t_token **lst_token);
void	free_all(t_token **lst_token, t_env **env);

/*********************************/
/*            builtins           */
/*********************************/
int		cmd_env(t_env **env);
void	ft_echo(char *option);
void	cmd_exit(char *option);
void	cmd_unset(t_section *sec);

/*********************************/
/*             export            */
/*********************************/
int		check_var_name(char *name);
int		cmd_export(t_section *sec);
int		existing_var(t_env **env, char *line);
int		mod_exist_var(t_env **env, char *line);

#endif

