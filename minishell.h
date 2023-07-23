/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/23 13:14:23 by ntardy           ###   ########.fr       */
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

int		ft_strlen(const char *str);
int		ft_strcat_pars(char *abs_path, char *path, char *cmd, char sep);
int		ft_isspace(char c);
int		space_only(char *p);
char	*first_word(char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, int start, int len);
char	**ft_split(char const *s, char c);

typedef struct s_token
{
	char *cmd;
	char *absolut_path;
	char *options;
	char *redir;
	char *operateur;
	struct s_token *next;
}	t_token;

int	parsing(char *input, t_token *list_token);
int		general_exe(t_token *token);

#endif
