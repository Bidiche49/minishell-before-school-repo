/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augustindrye <augustindrye@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:24:29 by augustindry       #+#    #+#             */
/*   Updated: 2023/07/21 17:43:17 by augustindry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include <stddef.h>

int	ft_execute_cmd(t_token *token)
{
	char	*path;
	char	*sep = { '/t', '/r', '/v', '/f', '/r', ' '};
	char	envp[] = {NULL};
	int		res;
	
	path = token->absolut_path;
	res = execve(path, ft_split(token->options, sep), envp);
	if (res == -1)
		perror();
	return (0);
}

int	ft_strlen_split(char *str, char *sep)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (sep[j])
		{
			if (sep[j] == str[i] && sep[j] == str[i + 1])
				i--;
			j++;
		}
		i++;
	}
	return (i);
}

char	*ft_strcmp_split(char *src, char *sep)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * ft_strlen_split(src, sep) + 1);
	if (!dest)
		return (1);
	while (src[i])
	{
		if (sep[j] == src[i] && sep[j] == src[i + 1])
			i++;
		else 
		{
			dest[j] = src[i];
			j++;
			i++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

int	ft_strlen_split_n(char *src, char *sep)
{
	int	i;
	int	j;
	int	cmp;

	i = 0;
	cmp = 0;
	while (src[i])
	{
		j = 0;
		while (sep[j])
		{
			if (sep[j] == src[i])
				cmp++;
			j++;
		}
		i++;
	}
	return (cmp);
}

int ft_strcmp(char c, char *sep)
{
	int	i;
	
	i = 0;
	if (!sep)
		return (0);
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_split(char *src, char *sep)
{
	char	**split;
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	src = ft_strcmp_split(src, sep);
	split = malloc(sizeof(char *) * ft_strlen_split_n(src, sep) + 1);
	if (!split)
		return (1);
	while (src[i])
	{
		if (ft_strcmp(src[i], sep) == 1)
		{
			j++;
			i++;
			n++;
			split[j][n] = '\0';
			n = 0;
		}
		split[j][n] = src[i];
	}
	free(src);
	split[j] = '\0';
	return (split);
}