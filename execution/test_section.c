/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_section.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:24:57 by audrye            #+#    #+#             */
/*   Updated: 2023/09/02 03:09:06 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void print_section(t_section *section)
// {
// 	while (section)
// 	{
// 		printf("/// print_section \\\\\n");
// 		printf("%s\n", section->cmd);
// 		printf("%s\n", section->abs_path);
// 		printf("%s\n", section->option);
// 		printf("%d\t%d\n", section->fd[0], section->fd[1]);
// 		printf("%d\t%d\n", section->pipe[0], section->pipe[1]);
// 		printf("%d\n", section->deep);
// 		printf("%d\t%d\n", section->fd[0], section->fd[1]);
// 		printf("%d\t%d\n", section->pipe[0], section->pipe[1]);
// 		print_token(section->token);
// 		section = section->next;
// 	}
// }