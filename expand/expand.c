/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 03:08:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 22:57:22 by ntardy           ###   ########.fr       */
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
			(*token)->str[i] = (*token)->str[i + 1];
		return (0);
	}
	else if ((*token)->str && (is_num((*token)->str[1]) == 1
			|| (*token)->str[1] == '$'))
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

int	if_forest(t_token *token)
{
		if (token->next && token->type == WORD
			&& token->next->type == WORD)
			return (0);
		else if (token->next && token->next->type == WORD
			&& token->next->str == NULL)
			return (0);
		else if (token->next && token->next->type == D_QUOTES
			&& token->next->str == NULL)
			return (0);
		else if (token->next && token->next->type == S_QUOTES
			&& token->next->str == NULL)
			return (0);
		else if (!token->next && token->type == SEPARATOR)
			return (0);
		else if (token->next && token->type == SEPARATOR
			&& token->next->type == SEPARATOR)
			return (0);
		else if (!token->next && is_op(token))
			return (0);
	return (1);
}

int	is_type_wq(t_token *token)
{
	if (token->type == WORD || token->type == S_QUOTES || token->type == D_QUOTES)
		return (1);
	return (0);
}

int	first_tok_null(t_token *list_token)
{
	if (list_token->next && is_type_wq(list_token) && !list_token->str
		&& is_type_wq(list_token->next) && list_token->next->str)
		return (0);
	if (list_token->next && is_type_wq(list_token) && !list_token->str
		&& list_token->next->type == SEPARATOR && list_token->next->next
		&& is_type_wq(list_token->next->next) && list_token->next->next->str)
		return (0);
	if (list_token->next && list_token->type == SEPARATOR
		&& is_type_wq(list_token->next) && list_token->next->str)
		return (0);
	return (1);
}

int	is_token_ok(t_token *list_token)
{
	if (first_tok_null(list_token) == 0)
		return (0);
	while (list_token)
	{
		if (list_token->next && is_op(list_token))
			return (1);
		if (if_forest(list_token) == 0)
			return (0);
		list_token = list_token->next;
	}
	return (1);
}

void	del_all_token(t_token **list_token)
{
	t_token	*tmp;

	tmp = *list_token;
	while (tmp->next)
		del_next_token(&tmp);
	tmp->type = WORD;
	if (tmp->str)
		free(tmp->str);
	tmp->str = NULL;
}

void	clean_first_token(t_token **list_token)
{
	t_token	*tmp;

	tmp = *list_token;
	(*list_token) = (*list_token)->next;
	if (tmp->str)
		free(tmp->str);
	free(tmp);
}

void	clean_token(t_token **list_token)
{
	t_token	*tmp;

	tmp = *list_token;
	if (first_tok_null(*list_token) == 0)
		clean_first_token(list_token);
	while (tmp)
	{
		if (tmp->next && tmp->next->type == SEPARATOR && !tmp->next->next)
			del_next_token(&tmp);
		if (tmp->next && tmp->next->type == WORD && !tmp->next->str)
			del_next_token(&tmp);
		if (tmp->next && tmp->next->type == D_QUOTES && !tmp->next->str)
			del_next_token(&tmp);
		if (tmp->next && tmp->next->type == S_QUOTES && !tmp->next->str)
			del_next_token(&tmp);
		if (tmp->next && tmp->type == SEPARATOR && tmp->next->type == SEPARATOR)
			del_next_token(&tmp);
		if (!tmp->next && is_op(tmp))
			return (del_all_token(list_token), (void)0);
		tmp = tmp->next;
	}
}


void print_lsttoken(t_token *list_token)
{
	printf("print_toke\n");
	while (list_token)
	{
		printf("[");
		if (list_token->type == WORD)
			printf("WORD");
		if (list_token->type == SEPARATOR)
			printf("SEPARATOR");
		if (list_token->type == D_QUOTES)
			printf("D_QUOTES");
		if (list_token->type == S_QUOTES)
			printf("S_QUOTES");
		if (list_token->type == OUT)
			printf("OUT");
		if (list_token->type == IN)
			printf("IN");
		if (list_token->type == HEREDOC)
			printf("HEREDOC");
		if (list_token->type == APPEND)
			printf("APPEND");
		if (list_token->type == PIPE)
			printf("PIPE");
		printf(" =");
		if (list_token)
			printf("%s", list_token->str);
		printf("] ");

		list_token = list_token->next;
	}
	printf("\n");
}


int	expand(t_token **list_token, t_env **env)
{
	t_token	*tmp;

	tmp = *list_token;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str && tmp->str[0] == '$'
			&& tmp->str[1] && is_alnum_und(tmp->str[1]))
			if (expand_word(&tmp, env) == ERROR)
				return (free_all(list_token, env), ERROR);
		tmp = tmp->next;
	}
	while (!isexpand_ok(*list_token))
	{
		if (expand_d_quotes(list_token, *env) == ERROR)
			return (free_all(list_token, env), ERROR);
		if (expand_to_token(list_token) == ERROR)
			return (free_all(list_token, env), ERROR);
		break ;
	}
	while (!is_token_ok(*list_token))
	{
		clean_token(list_token);
	}
	return (SUCCESS);
}
/*
!!!!!!!!!!!!!!!!!!!!!!!!!A GERER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bien gerer la lecture des variable d'environnement-------------------------------------------------------------------------------OK
(si le premier caractere apres le $ est un chiffre,------------------------------------------------------------------------------OK
considerer la suite comme un word : echo $0HBDHUE        {value$0}HBDHUE)--------------------------------------------------------OK

gerer aussi $?   = 0 normalement ok----------------------------------------------------------------------------------------------OK
gerer [SEPARATOR =(null)] [WORD =(null)] [SEPARATOR =(null)]
gerer les \$ \ en gerneral-------------------------------------------------------------------------------------------------------OK


gerer echo | $gggrtg    -ou-  echo | uerigh--------------------------------------------------------------------------------------OK
doit garder le mot apres le pipe-------------------------------------------------------------------------------------------------OK
gerer iggi | $vintg--------------------------------------------------------------------------------------------------------------OK


echo "$USER$$$\$HOME$UHO$UINJ$$$"------------------------------------------------------------------------------------------------OK
[WORD =echo] [SEPARATOR =(null)]-------------------------------------------------------------------------------------------------OK
[D_QUOTES =ntardy/mnt/nfs/homes/ntardy$] (manque un$etun\)-----------------------------------------------------------------------OK
echo "$$" ko---------------------------------------------------------------------------------------------------------------------OK
gerer les double $$ dans les D_QUOTES quand l'expand est pas detecte-------------------------------------------------------------OK
*/
