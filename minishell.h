/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/20 19:12:21 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int	ft_strlen(const char *str);

typedef struct s_token
{
	char *cmd;
	char *absolut_path;
	char **options;
	int nb_options;
	char *redir;
	char **args;
	int nb_args;
	char *operateur;
	struct token *next;
}	t_token;



#endif
