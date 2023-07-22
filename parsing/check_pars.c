/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:41:47 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 15:59:44 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_command(t_token *list_token, char **list_path)
{
	int	i;

	i = 0;
	while (list_path[i])
	{
		list_token->absolut_path = malloc(sizeof(char) * (ft_strlen(list_path[i]) + ft_strlen(list_token->cmd) + 2));
		if (list_token->absolut_path == NULL)
			return (ft_error(", malloc error!"));
		if (ft_strcat_pars(list_token->absolut_path, list_path[i], list_token->cmd, '/') == 1)
			return (free(list_token->absolut_path), 1);
		if (access(list_token->absolut_path, F_OK) == 0)
		{
			if (access(list_token->absolut_path, X_OK) == 0)
				return (0);
		}
		free(list_token->absolut_path);
		i++;
	}
	if (ft_strcat_pars(list_token->absolut_path, "command not found:", list_token->cmd, ' ') == 1)
		return (free(list_token->absolut_path), 1);
	return (0);
}

int	is_real_command(t_token *list_token)
{
	char	*path;
	char	**list_path;

	path = getenv("PATH");
	list_path = ft_split_pars(path, ':');
	if (list_path == NULL)
		return (1);
	if (check_command(list_token, list_path) == 1)
		return (1);
	return (0);
}

int	is_there_operator(char *input, int i, t_token *list_token)
{
	while (input[i])
	{
		i++;
		if (input[i - 1] == '|')
		{
			if (list_token->next)
			{
				list_token->operateur = malloc(sizeof(char) * 2);
				if (list_token->operateur == NULL)
					return (ft_error(", malloc KO !"), -1);
				list_token->operateur = "|";
			}
			break;
		}
	}
	return (i);
}
