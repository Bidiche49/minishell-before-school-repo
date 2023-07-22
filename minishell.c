/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 16:12:07 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	print_token(t_token *list_token)
{
	int	i;

	i = 1;
	while (list_token)
	{
		printf("list_token(%d)->cmd = %s\n", i, list_token->cmd);
		printf("list_token(%d)->absolut_path %s\n", i, list_token->absolut_path);
		printf("list_token(%d)->options %s\n", i, list_token->options);
		printf("list_token(%d)->operateur = %s\n", i, list_token->operateur);
		// if (list_token->operateur != NULL)
		// {
		// 	if (list_token->next)
		// 		printf(" %s ", list_token->operateur);
		// 	else
		// 		printf(" %s", list_token->operateur);
		// }
		list_token = list_token->next;
		i++;
	}
	printf("\n");
}

int main(int argc, char **argv) {
	char	*input;
	t_token	list_token;

	(void)argv;
	if (argc != 1)
		return (printf("No arg please, just \"./minishell\"\n"), 1);
	while(1) {
		input = readline("Minishell > ");
		if (input == NULL) {
			// L'utilisateur a appuyé sur Ctrl+D pour quitter le programme
			printf("\nFin du programme.\n");
			break;
		}
		if (ft_strlen(input) > 0)
		{
			add_history(input);
		}
		if (parsing(input, &list_token) == 1)
			return (1);
// test
		print_token(&list_token);
//test end
		free(input);
	}
	return 0;
}
