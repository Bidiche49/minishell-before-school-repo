/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:30:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/10 16:32:29 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_line(char *line)
{
	int	i;

	i = check_var_name(line);
	if (i == 0)
		return (error_export(line), 0);
	return (1);
}

int	mod_exist_var(t_env **env, char *line)
{
	t_env	*tmp;
	int		len_name;
	char	*name;

	tmp = *env;
	len_name = ft_strlen_char(line, '=');
	name = line;
	name[len_name] = '\0';
	while(tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (tmp->content)
				free(tmp->content);
			tmp->content = ft_strdup(line + len_name + 1);
			if (!tmp->content)
				return (malloc_error(), ERROR);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_env(t_env **env, t_token *tok)
{
	printf("tok->str = %s\n", tok->str);
	while (tok)
	{
		if (tok->type == WORD)
		{
			if (existing_var(env, tok->str))
			{
				printf("existing_var\n");
				if (mod_exist_var(env, tok->str) == ERROR)
					return (ERROR);
			}
			else if (check_line(tok->str))
			{
				printf("check_line ok\n");
				if (ft_lstadd_back_env(env, fill_new_env(tok->str)))
					return (malloc_error(), ERROR);
			}
			tok = tok->next;
		}
		else if (tok->type == SEPARATOR)
			tok = tok->next;
		else
			break ;
	}
	return (SUCCESS);
}

void	print_env_export(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if (tmp->name && tmp->content)
		{
			printf(BOLD YELLOW "export" RESET);
			printf(YELLOW " %s=" RESET, tmp->name);
			printf(CYAN "\"%s\"\n" RESET, tmp->content);
		}
		if (tmp->name && !tmp->content)
		{
			printf(BOLD YELLOW "export" RESET);
			printf(YELLOW " %s\n" RESET, tmp->name);
		}
		tmp = tmp->next;
	}
}

t_token	*find_tok(t_token *tok)
{
	t_token		*tmp;

	tmp = tok;
	while (tmp)
	{
		if (!ft_strcmp(tmp->str, "export"))
		// {
		// 	if (i == nb_export)
				break ;
		// 	i++;
		// }
		tmp = tmp->next;
	}
	if (tmp && tmp->next && tmp->next->next && tmp->next->next->type == WORD)
		return (tmp->next->next);
	return (NULL);
}

int	cmd_export(t_section *sec)
{
	static int	nb_export = 0;

	if (!sec->option)
		return (ERROR);
	if (!ft_strcmp(sec->option, "export"))
		return (nb_export++, print_env_export(sec->env), SUCCESS);
	if (sec->deep)
		return (SUCCESS);
	if (add_env(sec->env, find_tok(sec->token)) == ERROR)
		return (ERROR);//FREE ALL---------------------------------------------------
	cmd_env(sec->env);
	return (SUCCESS);
}
