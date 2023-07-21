/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:31:21 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/21 23:14:03 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strcat_pars(char *abs_path, char *path, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i])
		abs_path[j++] = path[i++];
	abs_path[j++] = '/';
	i = 0;
	while (cmd[i])
		abs_path[j++] = cmd[i++];
	abs_path[j] = '\0';
	return (0);
}

int	is_real_command(t_token *list_token)
{
	char	*path;
	// char	*abs_path;
	char	**list_path;
	int		i;

	path = getenv("PATH");
	list_path = ft_split_pars(path, ':');
	if (list_path == NULL)
		return (1);
	i = 0;
	while (list_path[i])
	{
		list_token->absolut_path = malloc(sizeof(char) * (ft_strlen(list_path[i]) + ft_strlen(list_token->cmd) + 2));
		if (list_token->absolut_path == NULL)
			return (ft_error(", malloc error!"));
		if (ft_strcat_pars(list_token->absolut_path, list_path[i], list_token->cmd) == 1)
			return (free(list_token->absolut_path), 1);
		if (access(list_token->absolut_path, F_OK) == 0)
		{
			if (access(list_token->absolut_path, X_OK) == 0)
				return (0);
		}
		free(list_token->absolut_path);
		i++;
	}
	printf("nok\n");
	return (1);
}

int	fill_command(t_data *data, t_token *list_token)
{
	int		i;
	t_token *tmp;

	i = 0;
	tmp = list_token;
	while (list_token)
	{
		while (data->input[i] && data->input[i] == ' ')
			i++;
		list_token->cmd = first_word(&data->input[i]);
		if (list_token->cmd == NULL)
			return (ft_error(", malloc error !"));
		if (is_real_command(list_token) == 1)
			return (1);
		while (data->input[i])
		{
			i++;
			if (data->input[i - 1] == '|')
				break;
		}
		list_token = list_token->next;
	}
	list_token = tmp;
	return (0);
}

int	fill_tokens(t_data *data, t_token *list_token)
{
	fill_command(data, list_token);
	while (list_token)
	{
		printf("%s\n", list_token->cmd);
		list_token = list_token->next;
	}
	return (0);

	// list_token->cmd = first_word(data->input);
	// printf("%s\n", list_token->cmd);
}
