/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/22 16:28:51 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int		ft_strlen(const char *str);
int		ft_strcat_pars(char *abs_path, char *path, char *cmd, char sep);
char	*first_word(char *str);
char	*ft_strdup(const char *src);
char	**ft_split_pars(char const *s, char c);

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

#endif
