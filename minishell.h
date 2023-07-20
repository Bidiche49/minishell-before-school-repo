/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:31:41 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/20 18:46:55 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int	ft_strlen(const char *str);

typedef struct Commande
{
	char *cmd;
	char *absolut_path;
	char **options;
	int nb_options;
	char *redir;
	char **args;
	int nb_args;
	char *operateur;
	struct Commande *next;
}

#endif
