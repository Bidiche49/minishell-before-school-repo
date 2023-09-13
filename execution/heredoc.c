/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:43:05 by audrye            #+#    #+#             */
/*   Updated: 2023/09/13 04:27:12 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}

t_token *ft_newheredoc(char *str)
{
	t_token *new;

	if (!str)
		return (NULL);
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (malloc_error(), NULL);
	new->type = D_QUOTES;
	new->str = NULL;
	new->str = str;
	if (!new->str)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

int	build_heredoc(t_token *token, t_token *heredoc, t_env *env)
{
	if (heredoc != NULL)
		free_list_token(&heredoc);
	while (1)
	{
		if (ft_lstadd_back(&heredoc, ft_newheredoc(readline("> "))) == ERROR)
			return (free_list_token(&heredoc), malloc_error(), ERROR);
		if (ft_strcmp(token->str, lst_last(heredoc)->str) == 0)
			return(print_token(heredoc), expand_d_quotes(&heredoc, env),print_token(heredoc), SUCCESS);
	}
	return (SUCCESS);
}

int	list_to_file(t_token *heredoc, t_token *token, int nb_hd)
{
	int	fd;
	
	while (nb_hd > 0)
	{
		if (token->type == HEREDOC && token)
			nb_hd--;
		if (nb_hd == 0 && token->type == HEREDOC)
			break;
		token = token->next;
	}
	printf("nom du file = %s\n", token->str);
	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf(" valeur de fd = %d\n", fd);
	if (fd == -1)
		return (free_list_token(&heredoc), ERROR);
	while (heredoc != NULL)
    {
        write(fd, heredoc->str, ft_strlen(heredoc->str));
        write(fd, "\n", 1);
        heredoc = heredoc->next;
    }
	close(fd);
	return (free_list_token(&heredoc), SUCCESS);
}

int	how_many_heredoc(t_token *token)
{
	int	i;
	
	i = 0;
	while (token)
	{
		if (token->type == HEREDOC)
			i++;
		token = token->next;
	}
	return (i);
}

int	all_heredoc(t_token *token, t_env *env)
{
	t_token *heredoc;
	t_token *tmp_token;
	int	nb_heredoc;
	int	nb_hd;

	heredoc = NULL;
	tmp_token = token;
	nb_heredoc = how_many_heredoc(token);
	nb_hd = nb_heredoc;
	signal(SIGINT, &signal_heredoc);
	while (tmp_token)
	{
		if (nb_heredoc == 0)
			break;
		if (tmp_token->type == HEREDOC && tmp_token->str)
		{
			if (build_heredoc(tmp_token, heredoc, env) == ERROR)
				return (free_list_token(&heredoc), malloc_error(), ERROR);
			nb_heredoc--;
		}
		tmp_token = tmp_token->next;
	}
	//printf("ecrit dans le fichier = %s\n", heredoc->str);
	if (list_to_file(heredoc, token, nb_hd) == ERROR)
		return(malloc_error(), ERROR);
	return (SUCCESS);
}
