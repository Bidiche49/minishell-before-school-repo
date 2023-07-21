/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/21 23:08:41 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int		ft_strlen(const char *str);
char	*first_word(char *str);
char	*ft_strdup(const char *src);
char	**ft_split_pars(char const *s, char c);

typedef struct s_token
{
	char *cmd;
	char *absolut_path;
	char **options;
	char *redir;
	char *operateur;
	struct s_token *next;
}	t_token;

t_token	*parsing(char *input);

#endif
