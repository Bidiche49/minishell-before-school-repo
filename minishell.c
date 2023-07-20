/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/07/20 18:10:15 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while(1) {
        input = readline("Minishell ");
        if (input == NULL) {
            // L'utilisateur a appuyé sur Ctrl+D pour quitter le programme
            printf("\nFin du programme.\n");
            break;
        }

        // Traitez l'entrée de l'utilisateur ici (par exemple, exécutez la commande)

        // Ajoutez l'entrée à l'historique pour que l'utilisateur puisse la rappeler avec les flèches
        add_history(input);

        // Libérez la mémoire allouée par readline pour l'entrée
        free(input);
    }

    return 0;
}
