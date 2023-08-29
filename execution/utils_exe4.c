/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:19:32 by audrye            #+#    #+#             */
/*   Updated: 2023/08/29 02:47:54 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

int	ft_strcat_exec_sec_d(t_section *section, char *exec)
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
