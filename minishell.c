/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/22 23:39:27 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

// void	ctrl_c_hdoc(int sig)
// {
// 	(void) sig;
// 	close(0);
// 	printf("\n");
// }

// void	handle_signal_hdoc(void)
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, &ctrl_c_hdoc);
// }

// void	handle_signal(int sigid)
// {
// 	if (sigid == SIGINT)
// 	{
// 		write(2, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	if (sigid == SIGQUIT)
// 		return ;
// }

// void	set_signal(void)
// {
// 	signal(SIGINT, &handle_signal);
// 	signal(SIGQUIT, SIG_IGN);
// }

void print_token(t_token *list_token)
{
	int i;

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

// void sigint_handler(int signum)
// {
// 	(void)signum;
// 	printf("\n");			// Affiche un message
// 	rl_on_new_line();		// Place le curseur sur une nouvelle ligne
// 	rl_replace_line("", 0); // Efface le contenu de la ligne actuelle
// 	rl_redisplay();			// Affiche le prompt de nouveau
// }

int main(int argc, char **argv)
{
	char *input;
	t_token list_token;

	(void)argv; // Cette ligne supprime un avertissement de compilation indiquant que la variable argv n'est pas utilisée.
	// signal(SIGINT, sigint_handler); // Définit le gestionnaire de signal SIGINT (CTRL-C) avec la fonction sigint_handler.
	if (argc != 1)
	{
		printf("No arg please, just \"./minishell\"\n"); // Affiche un message si l'utilisateur a passé des arguments en ligne de commande.
		return 1;										 // Quitte le programme avec le code de retour 1 (erreur) en cas d'argument en ligne de commande.
	}
	while (1)
	{
		input = readline("Minishell > "); // Affiche le prompt "Minishell > " et attend l'entrée de l'utilisateur.
		if (input == NULL) // Vérifie si l'entrée est NULL, ce qui indique généralement la fin de l'entrée.
			break;		   // Sort de la boucle si l'entrée est NULL (généralement quand l'utilisateur appuie sur CTRL-D).
		if (ft_strlen(input) > 0 && space_only(input) == 0) // Vérifie si l'entrée n'est pas vide et ne contient pas que des espaces.
		{
			add_history(input); // Ajoute l'entrée à l'historique de readline pour qu'elle puisse être rappelée avec les flèches du clavier.
			if (parsing(input, &list_token) == 1) // Appelle la fonction parsing pour analyser l'entrée et stocker les jetons dans list_token.
				return 1;						  // Quitte le programme avec le code de retour 1 (erreur) si la fonction parsing retourne 1.

			// test
			print_token(&list_token); // Affiche les jetons (tokens) analysés à des fins de test.
			// test end

			general_exe(&list_token); // Appelle la fonction general_exe pour exécuter la commande en utilisant les jetons analysés.
		}
		free(input); // Libère la mémoire allouée pour stocker l'entrée de l'utilisateur.
	}
	return 0; // Retourne 0 (succès) à la fin du programme.
}
