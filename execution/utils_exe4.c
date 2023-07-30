/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:19:32 by audrye            #+#    #+#             */
/*   Updated: 2023/07/30 02:04:06 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	while (section->option[i])
		tmp[i] = section->option[i++];
	while (exec[j])
	{
		tmp[i] = exec[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	free(section->option);
	section->option = tmp;
	return (SUCCES);
}