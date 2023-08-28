/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 01:03:58 by audrye            #+#    #+#             */
/*   Updated: 2023/08/28 00:13:09 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	ft_strcat_exec_sec(t_section *section, char *exec)
{
	int	i;
	int	j;
	int	len;
	char	*tmp;

	i = 0;
	j = 0;
	
	len = ft_strlen(section->option) + ft_strlen(exec);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (ERROR);
	while (section->option != NULL && section->option[i])
	{
		tmp[i] = section->option[i];
		i++;
	}
	while (exec[j])
	{
		tmp[i] = exec[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	free(section->option);
	section->option = tmp;
	return (SUCCESS);
}

int	ft_strcat_exec_sec_s(t_section *section, char *exec)
{
	int	i;
	int	j;
	int	len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(section->option) + ft_strlen(exec);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (ERROR);
	while (section->option != NULL && section->option[i])
	{
		tmp[i] = section->option[i];
		i++;
	}
	while (exec[j])
	{
		tmp[i] = exec[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	free(section->option);
	section->option = tmp;
	return (SUCCESS);
}

void	add_space(t_section *section)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(section->option) + 2));
	while (section->option[i])
	{
		tmp[i] = section->option[i];
		i++;
	}
	free(section->option);
	tmp[i] = ' ';
	tmp[i + 1] = '\0';
	section->option = tmp;
}

int	is_pipe(t_section *section)
{
	int	i;
	
	i = 0;
	while (section)
	{
		i++;
		section = section->next;
	}
	return (i);
}