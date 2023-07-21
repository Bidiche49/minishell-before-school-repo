/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/21 23:57:37 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"


int ft_execute_cmd(t_token *token)
{
    extern char **environ; // Importer l'environnement actuel du système
    int res;
    char *const opt[] = { "-l", NULL }; // Utilisez un tableau de pointeurs de caractères (tableau de chaînes)

    if (token == NULL)
        return (1);
    res = execve(token->absolut_path, opt, environ);
    if (res == -1)
        perror("KO\n");
    return (0);
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
		parsing(input, &list_token);
		free(input);
	}

	return 0;
}
