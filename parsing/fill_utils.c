/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:34:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/31 10:49:26 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_test_type(char *str, t_token *new)
{
	if (isspace(*str))
		new->type = SEPARATOR;
	else if (*str == '\'' || *str == '"')
		new->type = (S_QUOTES + (*str == '"'));
	else if (*str == '<' && *(str + 1) && *(str + 1) == '<')
		new->type = HEREDOC;
	else if (*str == '>' && *(str + 1) && *(str + 1) == '>')
		new->type = APPEND;
	else if (*str == '<')
		new->type = IN;
	else if (*str == '>')
		new->type = OUT;
	else if (*str == '|' && *(str +1) == '|')
		new->type = -1;
	else if (*str == '|')
		new->type = PIPE;
	else
		new->type = WORD;
}

int ft_strlen_remake(char *str, int type)
{
	int i;

	i = 0;
	if (type == WORD)
	{
		if (str[0] == '$')
			i++;
		while (str[i] && !is_sep_op(str[i]))
			i++;
	}
	else
	{
		if (type == S_QUOTES)
		{
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (type == D_QUOTES)
		{
			while (str[i] && str[i] != '"')
				i++;
		}
		if (!str[i])
			return (-1);
	}
	return (i);
}

int ft_strdup_remake(char *str, t_token *new)
{
	int i;
	int len;
	char c;

	i = 0;
	if (str[0] == '$' && str[1] && str[1] == '$')
	{
		new->type = WORD;
		new->str = NULL;
		printf("str = %s\n", str);
		return (SUCCESS);
	}
	if (new->type == WORD )
		c = ' '; // ATTENTION GERER POUR LES WORDS QUI NE SARRETTENT QUE POUR ESPACE
	else if (new->type == S_QUOTES)
	{
		c = '\'';
		str++;
	}
	else if (new->type == D_QUOTES)
	{
		c = '"';
		str++;
	}
	else
	{
		new->str = NULL;
		return (SUCCESS);
	}
	len = ft_strlen_remake(str, new->type);
	if (len == -1)
		return (write(0, ERR_QUOTES_OPEN, ft_strlen(ERR_QUOTES_OPEN)), ERROR);
	if (len == 0)
		return (new->str = NULL, SUCCESS);
	new->str = malloc(sizeof(char) * (len + 1));
	if (new->str == NULL)
		return (malloc_error(), ERROR); // malloc error
	while (*str && i < len && *str != c)
		new->str[i++] = *str++;
	new->str[i] = '\0';
	return (SUCCESS);
}

t_token *ft_newtoken(char *str)
{
	t_token *new;

	if (str == NULL)
		return (NULL);  // error fill token
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (malloc_error(), NULL);
	ft_test_type(str, new);
	// if (new->type == -1)
	// 	return (free(new), NULL); //syntax error near unexpected token `|'
	if (ft_strdup_remake(str, new) == ERROR)
		return (malloc_error(), free(new), NULL);
	new->next = NULL;
	return (new);
}

int	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token *actu;

	if (new == NULL)
		return (ERROR);
	if (*lst == NULL)
	{
		*lst = new;
		return (SUCCESS);
	}
	actu = *lst;
	while (actu->next != NULL)
		actu = actu->next;
	actu->next = new;
	return (SUCCESS);
}
