/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 01:03:58 by audrye            #+#    #+#             */
/*   Updated: 2023/08/06 18:47:03 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"
#include "../minishell.h"

// static char const *const g_meta_tab_s = {
// '*','?','[',']','|','>','<','\'','\"','`',';','&',
// '\\','$','\n','\t','\r','\b','\f','\v'
// };
// static char const *const g_meta_tab_d = {
// '*','?','[',']','|','>','<','\'','\"','`',';','&',
// '\\','\n','\t','\r','\b','\f','\v'
// };


// int	is_meta_c(char *simple_c)
// {
// 	int	i;
// 	int j;
// 	int	meta;

// 	i = 0;
// 	meta = 0;
// 	while (simple_c[i])
// 	{
// 		j = 0;
// 		while (g_meta_tab_s[j])
// 		{
// 			if (simple_c[i] == g_meta_tab_s[j])
// 				meta++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (meta);
// }

// int	is_meta_d(char *simple_d)
// {
// 	int	i;
// 	int j;
// 	int	meta;

// 	i = 0;
// 	meta = 0;
// 	while (simple_d[i])
// 	{
// 		j = 0;
// 		while (g_meta_tab_d[j])
// 		{
// 			if (simple_d[i] == g_meta_tab_d[j])
// 				meta++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (meta);
// }

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