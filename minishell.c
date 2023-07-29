/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/29 01:46:12 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

void print_token(t_token *list_token)
{
	printf("print_toke\n");
	while (list_token)
	{
		printf("[");
		if (list_token->type == WORD)
			printf("WORD");
		if (list_token->type == SEPARATOR)
			printf("SEPARATOR");
		if (list_token->type == D_QUOTES)
			printf("D_QUOTES");
		if (list_token->type == S_QUOTES)
			printf("S_QUOTES");
		if (list_token->type == OUT)
			printf("OUT");
		if (list_token->type == IN)
			printf("IN");
		if (list_token->type == HEREDOC)
			printf("HEREDOC");
		if (list_token->type == APPEND)
			printf("APPEND");
		if (list_token->type == PIPE)
			printf("PIPE");
		printf(" =");
		if (list_token)
			printf("%s", list_token->str);
		printf("] ");

		list_token = list_token->next;
	}
	printf("\n");
}

void sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int argc, char **argv)
{
	char *input;
	t_token *list_token;

	list_token = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("No arg please, just \"./minishell\"\n");
		return (ERROR);
	}
	while (1)
	{
		input = readline("Minishell > ");
		if (input == NULL)
			break ;
		if (ft_strlen(input) > 0 && space_only(input) == 1)
		{
			add_history(input);
			if (parsing(input, &list_token) == 1)
				return (ERROR);
/*----------------------TESTS----------------------*/
			// printf("lst_token->str 1= %s\n", list_token->str);
			print_token(list_token);
			// free_all(&list_token);
			// free(input); // Libère la mémoire allouée pour stocker l'entrée de l'utilisateur.
			// exit (0);
/*---------------------TESTS_END----------------------*/
		}
		free(input);
	}
	return (SUCCESS);
}
