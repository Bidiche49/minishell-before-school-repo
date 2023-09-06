/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:45:21 by audrye            #+#    #+#             */
/*   Updated: 2023/09/05 14:34:25 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include "minishell.h"

int	ft_countword(char const *s, char c);
char	**ft_split(char const *s, char c);


void	malloc_error()
{
	fprintf(stderr, "fais pas chier\n");
}

// ls | lsblk > a | cat | grep e | echo lol | wc -l
// ls ECRIT vers lsblk
// lsblk LIT vers ls
// lsblk ECRIT vers cat
// cat LIT vers lsblk
// cat ECRIT vers grep
// grep LIT vers cat
// grep ECRIT vers echo
// echo LIT vers grep
// echo ECRIT vers wc
// wc LIT vers echo

// if (i != 0) // lsblk cat grep echo wc
// 	dup2(precedent, STDIN_FILENO)
// 	LIT vers derriere
// if (i != derniere) // ls lsblk cat grep echo
// 	dup2(avant, STDOUT_FILENO)
// 	ECRIT vers devant

void	*redirection(int fd[2], int index, int last, int prev)
{
	if (index != 0)
		dup2(prev, STDIN_FILENO);
	if (index != last)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	
	// pour heredoc / in, out / append
	// openfiles(	)
	/*
	int fd;
	while (fichier[i])
	{
		if (fichier[i].type == '>')
			fd = open blabla
			if (fd == -1)
				exit(1)
	}
	*/
}

int main(int ac, char **av)
{
	int fd[2];
	int prev = -1;
	while (1)
	{
		// ls | grep a | wc -l
		char *str = readline("> ");
		if (!str)
			exit(1);
		if (!*str)
			continue;
		char **tab = ft_split(str, '|');
		int nbcmd = ft_countword(str, '|');
		free(str);
		int i =  0;
		int *pid = malloc(sizeof(int) * nbcmd);
		while (i < nbcmd)
		{
			pipe(fd);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				free(pid);
				printf("dans le fork\n");
				redirection(fd, i, nbcmd - 1, prev);
				char **arg = ft_split(tab[i], ' ');
				char *cmd = arg[0];
				execvp(cmd, arg);
				fprintf(stderr, "%s command not found\n", cmd);
				exit(127);
			}
			else if (pid[i] > 0)
			{
				fprintf(stderr, "%i %i %i\n", fd[0], fd[1], prev);
				close(fd[1]);
				if (i > 0)
					close(prev);
				prev = fd[0];
			}
			i++;
		}
		i = 0;
		while (i < nbcmd)
			waitpid(pid[i++], NULL, 0);
		close(fd[0]);
	}
}
