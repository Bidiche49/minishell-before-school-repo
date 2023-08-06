/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/08/06 14:55:53 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	check_cmd(char *src, char *env, t_section *section)
{
	char	**tmp;
	int	i;
	
	i = 0;
	tmp = ft_split(env, ':');
	printf("rentre dans check cmd\n");
	while (tmp[i])
	{
		if (access(tmp[i], F_OK) != -1)
		{
			if (access(tmp[i], X_OK) != -1)
			{
				if (ft_strcat_token(tmp[i], src, section) != 0)
					return (ERROR);
				if (ft_strcpy_token(src, section) != 0)
					return (ERROR);
				return (SUCCES);
			}
		}
		i++;
	}
	printf("sort de check cmd\n");
	return (SUCCES);
}

void	find_cmd(t_token *token, t_section *section)
{
	char	*env;
	
	printf("rentre dans find cmd\n");
	env = getenv("PATH");
	printf("PATH = \t%s\n", env);
	printf("valeur de str = %s\n", token->str);
	if (token->type == WORD) 
	{
		printf("est dans la boucle\n");
		if (check_cmd(token->str, env, section) != 0)
			section->cmd = NULL;
	}
	printf("passe le if\n");
	while (token)
	{
		if (token->type == PIPE)
			if (token->next->type == WORD)
				if (check_cmd(token->next->str, env, section) != 0)
					section->cmd = NULL;
		token = token->next;
	}
	printf("end find_cmd\n");
}			

int	gathering(t_token *token, t_section *section)
{
	while (token->type != PIPE)
	{
		if (token->type == SEPARATOR)
			section->option = add_space(section->option);
		else if (token->type == WORD || token->type == OUT || token->type == IN
					|| token->type == HEREDOC || token->type == APPEND)
		{
			if (ft_strcat_exec_sec(section, token->str) != 0)
				return (ERROR);
		}
		else if (token->type == S_QUOTES)
		{
			if (ft_strcat_exec_sec_s(section, token->str) != 0)
				return (ERROR);
		}
		else if (token->type == D_QUOTES)
		{
			if (ft_strcat_exec_sec_d(section, token->str) != 0)
				return (ERROR);
		}
		token = token->next;
	}
	return (SUCCES);
}

int	is_clear(t_token *token, t_section *section)
{
	printf("rentre dans is clear\n");
	find_cmd(token, section);
	printf("passe find_cmd\n");
	while (token)
	{
		if (token->type == PIPE)
			section = section->next;
		if (section->cmd != NULL)
		{
			if (gathering(token, section) != 0)
				return (ERROR);
		}
		token = token->next;
	}
	return (SUCCES);
}

int	exec_exe(t_section *section)
{
	if (execve(section->abs_path, ft_split(section->option, ' '), NULL) == -1)
		return (perror(section->abs_path), 1);
	return (0);
	
}

int	execution(t_token *token)
{
	t_section	list_section;
	
	printf("entre dans execution\n");
	init_list_section(token, &list_section);
	printf("passe init_section_list\n");
	if (is_clear(token, &list_section) != 0) // scan des differents token et verification de la validation des commandes
		return (ERROR); // free la structure
	if (exec_exe(&list_section) != 0)
		return (ERROR);
	return (SUCCES);
}
