/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 03:08:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/27 22:35:11 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	special_case_expand(t_token **token)
{
	int	i;

	i = 0;
	if ((*token)->str && (*token)->str[1] == '?')
	{
		(*token)->str[0] = '0';
		while ((*token)->str[i++])
		{
			printf("%c\n", (*token)->str[i]);
			(*token)->str[i] = (*token)->str[i + 1];
		}
		return (0);
	}
	else if ((*token)->str && (is_num((*token)->str[1]) == 1 || (*token)->str[1] == '$'))
	{
		if ((*token)->str[i + 2] == '\0')
			return (free((*token)->str), (*token)->str = NULL, 0);
		while ((*token)->str[i + 1])
		{
			(*token)->str[i] = (*token)->str[i + 2];
			i++;
		}
		return (0);
	}
	return (1);
}

int expand_word(t_token **token, t_env **env)
{
	t_env *tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		if (special_case_expand(token) == 0)
			return (SUCCESS);
		else if (is_in_env((*token)->str, tmp_env) == 1)
		{
			free((*token)->str);
			(*token)->str = ft_strdup(tmp_env->content);
			if (!(*token)->str)
				return (write(0, ERR_MALLOC_KO, ft_strlen(ERR_MALLOC_KO)), ERROR);
			return (SUCCESS);
		}
		tmp_env = tmp_env->next;
	}
	free((*token)->str);
	(*token)->str = NULL;
	return (SUCCESS);
}



int copy_var_env(char *dest, char *str, t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		if ((str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '$'))
			return (0);
		if (str[i + 1] == '?')
		{
			dest[i] = '0';
			return (2);
		}
		if (is_in_env(str, env) == 1)
		{
			// printf("str test = %s\n", str);
			while (env->content[i])
			{
				dest[i] = env->content[i];
				i++;
			}
			return (i);
		}
		env = env->next;
	}
	return (i);
}

int count_len_var_content(char *str, t_env *env)
{
	while (env)
	{
		if (is_in_env(str, env) == 1)
		{
			// printf("count_len_CONTENT %s = %d\n", str, ft_strlen(env->content));
			return (ft_strlen(env->content));
		}
		env = env->next;
	}
	return (0);
}

int count_len_var_name(char *str)
{
	int i;

	i = 0;
	if (str[i + 1] == ' ' || !str[i + 1])
		return (0);
	if (is_num(str[i + 1]) == 1 || str[i + 1] == '?' || str[i + 1] == '$' || str[i + 1] == '\\')
		return (2);
	while (str && str[i + 1] && is_alnum_und(str[i + 1]))
		i++;
	printf("len_VARNAME %s = %d\n", str + i + 1, i);
	return (i + 1);
}

char *dup_dquotes(int len_tot, char *str, t_env *env)
{
	char *d_quotes;
	int i;
	int j;

	(void)env;

	i = 0;
	j = 0;
	// printf("len_tot = %d\n",len_tot);
	d_quotes = malloc(sizeof(char) * len_tot);
	if (d_quotes == NULL)
		return (write(0, ERR_MALLOC_KO, ft_strlen(ERR_MALLOC_KO)), NULL);
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			// printf("char %c\n", str[i]);
			// printf("string %s\n", str + i);
			j += copy_var_env(d_quotes + j, str + i, env);
			i += count_len_var_name(str + i);
			if (str[i] && str[i] == '$' && (!str[i + 1] || str[i + 1] == ' '))
			{
				d_quotes[j++] = '$';
				i++;
			}
		}
		if (str[i] && str[i] != '$')
		{
			d_quotes[j++] = str[i++];
		}
	}
	if (str)
		free(str);
	d_quotes[j] = '\0';
	return (d_quotes);
}

int expand_d_quotes(t_token **list_token, t_env *env)
{
	t_token *tmp;
	int i;
	int len_tot;

	i = 0;
	tmp = *list_token;
	while (tmp)
	{
		len_tot = 0;
		if (is_an_exp_dquotes(tmp))
		{
			while (tmp->str && tmp->str[i])
			{
				if (tmp->str[i] == '$')
					len_tot += (count_len_var_content(tmp->str + i, env) - count_len_var_name(tmp->str + i));
				i++;
			}
			len_tot += i + 1;
			tmp->str = dup_dquotes(len_tot, tmp->str, env);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int expand_to_token(t_token **list_token)
{
	t_token *tmp;

	tmp = *list_token;
	while (tmp)
	{
		// if (tmp->next && tmp->next->type == SEPARATOR && !tmp->next->next)
		// 	del_next_token(&tmp);
		// if (tmp->next && tmp->next->type == WORD && !tmp->next->str)
		// 	del_next_token(&tmp);
		// if (tmp->next && tmp->type == SEPARATOR && tmp->next->type == SEPARATOR)
		// 	del_next_token(&tmp);
		if (tmp->next && tmp->type == WORD && tmp->next->type == WORD)
		{
			tmp->str = ft_strcat_dup(tmp->str, tmp->next->str);
			if (tmp->str == NULL)
				return (write(0, ERR_MALLOC_KO, ft_strlen(ERR_MALLOC_KO)), ERROR);
			del_next_token(&tmp);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int expand(t_token **list_token, t_env **env)
{
	t_token *tmp;

	tmp = *list_token;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str && tmp->str[0] == '$' && tmp->str[1])
			if (expand_word(&tmp, env) == ERROR)
				return (free_all(list_token, env), ERROR);
		tmp = tmp->next;
	}
	while (isexpand_ok(*list_token) == 1)
	{
		if (expand_d_quotes(list_token, *env) == ERROR)
			return (free_all(list_token, env), ERROR);
		if (expand_to_token(list_token) == ERROR)
			return (free_all(list_token, env), ERROR);
		break;
	}
	// while (is_token_ok(*list_token) == 1)
	// 	clean_token(list_token);
	return (SUCCESS);
}
/*
!!!!!!!!!!!!!!!!!!!!!!!!!A GERER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
supprimer les separator a la fin.
bien gerer la lecture des variable d'environnement (si le premier caractere apres le $ est un chiffre, considerer la suite comme un word : echo $0HBDHUE        {value$0}HBDHUE)
gerer aussi $?   = 0 normalement ok
gerer [SEPARATOR =(null)] [WORD =(null)] [SEPARATOR =(null)]
gerer les \$ \ en gerneral

*/
