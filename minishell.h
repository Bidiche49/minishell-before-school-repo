/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/29 15:10:28 by audrye           ###   ########.fr       */
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

# define SUCCESS 0
# define ERROR 1
# define NEW_LINE 2
# define MALL_KO 55
# define ERR_MANY_ARG "minishell: too many arguments\n"
# define ERR_ENV_KO "minishell: Error while retrieving the environment.\n"
# define ERR_MALLOC_KO "minishell: Error malloc\n"
# define ERR_QUOTES_OPEN "minishell: Error quote open\n"

extern int				g_error;

typedef enum e_type			t_type_token;
typedef struct s_token		t_token;
typedef struct s_env		t_env;

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

struct s_env{
	char	*name;
	char	*content;
	t_env	*next;
};

typedef struct s_file
{
	char	*name;
	int		type;
	struct s_file	*next;
}	t_file;

typedef struct s_section
{
	char	*cmd;
	char	*abs_path;
	char	*option;
	int		fd[2];
	int		pipe[2];
	int		deep;
	t_env	**env;
	struct s_token	*token;
	struct s_file	*file;
	struct s_section *next;
}	t_section;


int		ft_strlen(const char *str);
int		ft_strcat_pars(char *abs_path, char *path, char *cmd, char sep);
int		ft_isspace(char c);
int		space_only(char *p);
char	*first_word(char *str);
char	*ft_strdup(const char *src);
char	*ft_strcat_dup(char *dest, char *str);
char	*ft_substr(char const *s, int start, int len);
char	**ft_split(char const *s, char c);
int		is_num(char c);
int		is_alnum_und(char c);


int		parsing(char *input, t_token **list_token);
int		general_exe(t_token *token);
int		create_env(char **envd, t_env **env);
int		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*fill_new_env(char *line_env);
int		expand(t_token **list_token, t_env **env);
void	free_matrice(char **matrice);
void	err(char *str);
void	ft_putstr_fd(int fd, char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen_char(char *str, char c);
void	*ft_calloc(size_t nmemb, size_t size);


/* EXPORT */

int		contain_equal(char *line);
int		check_var_name(char *name);
int		existing_var(t_env **env, char *line);
void	error_export(char *line);
char	**fill_split_line(char *line_env);

/* SIGNAL */

void	config_minishell_signal(void);

/* FREE */

void free_list_token(t_token **lst_token);
void free_all(t_token **lst_token, t_env **env);

/* Execution */

int	execution(t_token *token, t_env **env);
int	master_exec(t_section *section);
void	end_of_exit(int *pid, int x, int y);
char	*ft_get_env(t_env	**env, char *str);
int	is_clear(t_token *token, t_section *section);

/* Utils_exe */

int	ft_lstsize(t_token *token);
int	ft_lstadd_back_exec(t_section **lst, t_section *new);
t_section	*ft_lstlast(t_section *lst);
void	init_list_section(t_token *token, t_section *section, t_env **env);
int	ft_lstsize_section(t_section *section);
t_file *ft_newsection_file(t_token *token);
int ft_lstadd_back_exec_file(t_file **lst, t_file *new);
void	init_file(t_token *token, t_file *file);

/* Utils_exe2 */

int	ft_strcat_token(char *path, char *cmd, t_section *section);
int	ft_strcpy_token(char *src, t_section *section);

/* Utils_exe3 */

int		ft_strcat_exec_sec(t_section *section, char *exec);
int		ft_strcat_exec_sec_s(t_section *section, char *exec);
int		ft_strcpy_exec_s(char *src, t_section *section);
int		ft_strcpy_exec_d(char *src, t_section *section);
int		is_meta_c(char *simple_c);
void	add_space(t_section *section);

/* Utils_exe3 */

int	is_meta_d(char *simple_d);
int	ft_strcat_exec_sec_d(t_section *section, char *exec);
int	is_back(char *str);
int	is_pipe(t_section *section);

/* REDIR */

int	is_redir(int type);
int	is_operator_exec(t_token *token);

/* PIPE */

int	exec_pipe(t_section *section, int x, int y);
int	open_all(t_section *section, t_file *file);
int file_open(t_section *section);
void	convert_file(int x, int y);
int	is_bultin(t_section *section);
int	util_dup2(t_section *section, int x, int y);
int	assigne_file(t_section *section, int *j, int i);
void	first_close_cmd(t_section *section, int n, int j);
void	last_close_cmd(t_section *section);
void	other_close_cmd(t_section *section, int n);
void	fork_apli(t_section *section, int *pid, int *j);
t_section	*next_section(t_section *section, int x, int *i);
void	kill_child(int num);
void	exec_cmd(t_section *section);
void	exec_not_pipe(t_section *section, int *pid, int *j);
int	fork_using(t_section *section, int *pid, int *j);
char	**ft_get_env_bis(t_env	**env);

int	cmd_env(t_env **env);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_echo(t_section *section);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
