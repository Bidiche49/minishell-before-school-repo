#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *command = "lsdfg";
    char *args[] = {command, "-l", NULL}; // Arguments de la commande ls
    char *env[] = {NULL}; // Aucune variable d'environnement supplémentaire

    if (execve(NULL, args, env) == -1) {
		printf("test\n");
        perror("/bin/lsdfg"); // Affiche un message d'erreur si l'exécution échoue
        exit(EXIT_FAILURE);
    }

    // Cette partie du code ne sera jamais atteinte si execve réussit.
    printf("Ce message ne sera pas affiché si execve réussit.\n");

    return 0;
}
