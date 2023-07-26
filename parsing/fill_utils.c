/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:34:59 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/26 23:06:19 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	calc_i(char *input, int token_passed)
// {
// 	int	i;

// 	i = 0;
// 	while (token_passed > 0)
// 	{
// 		while (input[i])
// 		{
// 			i++;
// 			if (input[i] && input[i - 1] == '|')
// 			{
// 				token_passed--;
// 				break ;
// 			}
// 		}
// 	}
// 	return (i);
// }

// int	malloc_option(t_token *list_token, char *input, int i)
// {
// 	int	len;

// 	len = 0;
// 	if (ft_isspace(input[i]))
// 		i++;
// 	while (input[i] && input[i] != '|')
// 	{
// 		if (ft_isspace(input[i]) && (input[i + 1] == '\0' || input[i + 1] == '|'))
// 				break ;
// 		len++;
// 		i++;
// 	}
// 	printf("len malloc_option = %d\n", len);
// 	list_token->options = malloc(sizeof(char) * (len + 1));
// 	if (list_token->options == NULL)
// 		return (ft_error(", malloc KO !"));
// 	return (0);
// }

int ft_strlen_remake(char *str, int type)
{
	int i;
	char c;

	i = 0;
	if (type == 0)
		c = ' '; // ATTENTION GERER POUR LES WORDS QUI NE SARRETTENT QUE POUR ESPACE
	if (type == 1)
		c = '\'';
	if (type == 2)
		c = '"';
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char *ft_strdup_remake(char *str, int type)
{
	unsigned int i;
	char *dest;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen_remake(str, type) + 1));
	if (dest == NULL)
		return (NULL);
	while (*str)
		dest[i++] = *str++;
	dest[i] = '\0';
	return (dest);
}

int ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token *actu;

	if (new == NULL)
		return (1);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	actu = *lst;
	while (actu->next != NULL)
		actu = actu->next;
	actu->next = new;
	return (0);
}

int ft_test_type(char *str)
{
	if (isspace(*str))
	{
		while (isspace(*str))
			*str++;
		return (SEPARATOR);
	}
	if (*str == '\'' || *str == '"')
	{
		str++; // Augmenter la valeur de str sans retourner de valeur
		return (S_QUOTES + (*str == '"'));
	}
	if (*str == '<' && *(str + 1) == '<')
	{
		str += 2; // Augmenter la valeur de str sans retourner de valeur
		return (HEREDOC);
	}
	if (*str == '>' && *(str + 1) == '>')
	{
		str += 2; // Augmenter la valeur de str sans retourner de valeur
		return (APPEND);
	}
	if (*str == '<')
	{
		str++; // Augmenter la valeur de str sans retourner de valeur
		return (IN);
	}
	if (*str == '>')
	{
		str++; // Augmenter la valeur de str sans retourner de valeur
		return (OUT);
	}
	else
		return (WORD);
}

t_token *ft_newtoken(char *str)
{
	t_token *new;
	int type;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	type = ft_test_type(str);
	if (str == NULL)
		new->str = NULL;
	else
	{
		new->str = ft_strdup_remake(str, type); // ATTENTION GERER POUR LES WORDS QUI NE SARRETTENT QUE POUR ESPACE
		if (new->str == NULL)
			return (free(new), NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}
