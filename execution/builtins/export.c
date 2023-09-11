/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:30:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/11 18:18:32 by audrye           ###   ########.fr       */
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

t_env* create_node(char *name, char *content) {
	t_env *new_node = malloc(sizeof(t_env));
	new_node->name = strdup(name);
	new_node->content = strdup(content);
	new_node->next = NULL;
	return new_node;
}

void insert_sorted(t_env **env, t_env *new_node) {
	t_env *current;

	if (*env == NULL || strcmp(new_node->name, (*env)->name) < 0) {
		new_node->next = *env;
		*env = new_node;
	} else {
		current = *env;
		while (current->next != NULL && strcmp(new_node->name, current->next->name) > 0) {
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

t_env* copy_and_sort_env(t_env *original_env) {
	t_env *sorted_env = NULL;
	t_env *current = original_env;

	while (current != NULL) {
		t_env *new_node = create_node(current->name, current->content);
		insert_sorted(&sorted_env, new_node);
		current = current->next;
	}

	return sorted_env;
}

// Fonction pour imprimer l'environnement trié
int	print_env_export(t_env **env) {
	t_env *sorted_env;

	sorted_env = copy_and_sort_env(*env);
	if (!sorted_env)
		return (malloc_error(), ERROR);
	while(sorted_env)
	{
		if (sorted_env->name && sorted_env->content)
		{
			printf(BOLD YELLOW "export" RESET);
			printf(YELLOW " %s=" RESET, sorted_env->name);
			printf(CYAN "\"%s\"\n" RESET, sorted_env->content);
		}
		if (sorted_env->name && !sorted_env->content)
		{
			printf(BOLD YELLOW "export" RESET);
			printf(YELLOW " %s\n" RESET, sorted_env->name);
		}
		sorted_env = sorted_env->next;
	}
	return (SUCCESS);
}

// void	print_env_export(t_env **env)
// {
// 	t_env *tmp;

// 	tmp = *env;
// 	while(tmp)
// 	{
// 		if (tmp->name && tmp->content)
// 		{
// 			printf(BOLD YELLOW "export" RESET);
// 			printf(YELLOW " %s=" RESET, tmp->name);
// 			printf(CYAN "\"%s\"\n" RESET, tmp->content);
// 		}
// 		if (tmp->name && !tmp->content)
// 		{
// 			printf(BOLD YELLOW "export" RESET);
// 			printf(YELLOW " %s\n" RESET, tmp->name);
// 		}
// 		tmp = tmp->next;
// 	}
// }

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
		return (nb_export++, print_env_export(sec->env));
	if (sec->deep > 1)
		return (SUCCESS);
	printf("cmd_export\n");
	if (add_env(sec->env, find_tok(sec->token)) == ERROR)
		return (printf("test\n"), ERROR);//FREE ALL---------------------------------------------------
	cmd_env(sec->env);
	return (SUCCESS);
}
