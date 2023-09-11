/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:34:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/11 18:31:47 by ntardy           ###   ########.fr       */
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

int ft_strlen_remake(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] != '\'' && str[0] != '"')
	{
		if (str[0] == '$')
			i++;
		while (str[i] && !is_sep_op(str[i]))
			i++;
	}
	else
	{
		if (str[0] == '\'')
			while (str[i + 1] && str[i + 1] != '\'')
				i++;
		else if (str[0] == '"')
			while (str[i + 1] && str[i + 1] != '"')
				i++;
		if (!str[i + 1])
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
	c = 0;
	if (str[0] == '$' && str[1] && str[1] == '$')
		return (new->type = WORD, new->str = NULL, SUCCESS);
	if (new->type == WORD )
		c = ' ';
	else if (new->type == S_QUOTES)
		c = '\'';
	else if (new->type == D_QUOTES)
		c = '"';
	len = ft_strlen_remake(str);
	if (len == 0 || c == 0)
		return (new->str = NULL, SUCCESS);
	if (new->type != WORD)
		str++;
	new->str = ft_calloc((len + 1), sizeof(char));
	if (new->str == NULL)
		return (malloc_error(), ERROR);
	while (*str && i < len && *str != c)
		new->str[i++] = *str++;
	return (SUCCESS);
}

t_token *ft_newtoken(char *str)
{
	t_token *new;

	if (str == NULL)
		return (NULL);  // error fill token
	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (malloc_error(), NULL);
	ft_test_type(str, new);
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
