/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/07 18:52:33 by audrye           ###   ########.fr       */
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
	// int		return_ft;
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
			add_history(input); // Ajoute l'entrée à l'historique de readline pour qu'elle puisse être rappelée avec les flèches du clavier.
			if (parsing(input, &list_token) == 1) // Appelle la fonction parsing pour analyser l'entrée et stocker les jetons dans list_token.
				return 1;			  // Quitte le programme avec le code de retour 1 (erreur) si la fonction parsing retourne 1.
			// print_token(list_token); // Affiche les jetons (tokens) analysés à des fins de test.
			if (execution(list_token) == 1)
				return 1;
			// test
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
