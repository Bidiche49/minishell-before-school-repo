/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/30 03:09:11 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_error;

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

int main(int argc, char **argv, char **envp)
{
	int		return_ft;
	char	*input;
	t_token	*list_token;

	list_token = NULL;
	(void)argv;
	(void)envp;
	config_minishell_signal();
	input =  NULL;
	if (argc != 1)
		return (write(0, ERR_MANY_ARG, ft_strlen(ERR_MANY_ARG)), ERROR);
	while (1)
	{
		input = readline("Minishell > ");
		if (input == NULL)
			break ;//malloc readline error
		if (ft_strlen(input) > 0 && space_only(input) == 1)
		{
			add_history(input);
			return_ft = parsing(input, &list_token);
			if (return_ft != 0)
			{
				if (return_ft == ERROR)
					return (ERROR);
				// if (return_ft == NEW_LINE)
				// 	ctrl_c();
			}
			/*----------------------TESTS----------------------*/
			// printf("lst_token->str 1= %s\n", list_token->str);
			// print_token(list_token);
			// free_all(&list_token);
			// free(input); // Libère la mémoire allouée pour stocker l'entrée de l'utilisateur.
			// exit (0);
			/*---------------------TESTS_END----------------------*/
		}
		free_list_token(&list_token);
		free_list_token(&list_token);
	}
	rl_clear_history();
	write(STDOUT_FILENO, "exit\n", 5);
	return (SUCCESS);
}
