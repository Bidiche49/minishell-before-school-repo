/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:45:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/11 21:03:28 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_env_var(t_env **actual)
{
	t_env	*tmp2;

	tmp2 = (*actual)->next->next;
	if ((*actual)->next->name)
		free((*actual)->next->name);
	if ((*actual)->next->content)
		free((*actual)->next->content);
	free((*actual)->next);
	(*actual)->next = tmp2;
}

void	del_first_env_var(t_env **lst)
{
	t_env	*tmp2;

	tmp2 = (*lst)->next;
	if ((*lst)->name)
		free((*lst)->name);
	if ((*lst)->content)
		free((*lst)->content);
	free((*lst));
	(*lst) = tmp2;
}

int	check_var_name_unset(char *line)
{
	int	i;

	i = 1;
	if (is_num(line[0]) || !is_alnum_und(line[0]))
		return (0);
	while (line[i] && (is_alnum_und(line[i])))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

void	del_in_env(t_env **env, t_token *tok)
{
	t_env	*tmp;

	tmp = *env;
	if (!check_var_name_unset(tok->str))
		return (error_export(tok->str), (void)ERROR);
	if (!ft_strcmp(tok->str, tmp->name))
		return (del_first_env_var(env), (void)SUCCESS);
	while (tmp)
	{
		if (tmp->next && !ft_strcmp(tok->str, tmp->next->name))
			return (del_env_var(&tmp), (void)SUCCESS);
		tmp = tmp->next;
	}
	return ;
}

void	del_var_env(t_env **env, t_token *tok)
{
	if (!tok->str)
		return ;
	while (tok)
	{
		if (tok->type == WORD)
			return(del_in_env(env, tok), (void)SUCCESS);
		if (tok && tok->next && tok->next->type == SEPARATOR && tok->next->next && tok->next->next->type == WORD)
			tok = tok->next->next;
		else
			break ;
	}
	return ;
}

void	cmd_unset(t_section *sec)
{
	t_token	*tok;

	tok = sec->token;
	if (sec->deep > 1)
		return ;
	if (tok && tok->next && tok->next->next && tok->next->next->type == WORD)
		return (del_var_env(sec->env, tok->next->next));
	return ;
}
