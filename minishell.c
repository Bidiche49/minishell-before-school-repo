/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/28 07:12:34 by audrye           ###   ########.fr       */
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

void	print_envd(char **env)
{
	int	i;

	i = 0;
	printf("\n\n env = \n");
	while (env[i])
		printf("%s\n", env[i++]);
}

void	print_env(t_env *env)
{
	while(env)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}

// int	isan_export(char *str)
// {
// 	int	nbequal;
// 	int	i;

// 	nbequal = 0;
// 	i = 0;
// 	if (!str)
// 		return
// 	while(str[i])
// }

// int	export(t_token *list_token, t_env *env)
// {
// 	if (list_token->next == NULL && list_token->type == WORD && isan_export(list_token->str))
// 	{

// 	}
// }

int main(int argc, char **argv, char **envd)
{
	// int		return_ft;
	char	*input;
	t_token	*list_token;
	t_env	*env;

	if (argc != 1)
		return (write(0, ERR_MANY_ARG, ft_strlen(ERR_MANY_ARG)), ERROR);
	if (!envd)
		return (write(0, ERR_ENV_KO, ft_strlen(ERR_ENV_KO)), ERROR);
	input = NULL;
	list_token = NULL;
	env = NULL;
	(void)argv;
	if (create_env(envd, &env) == ERROR)
		return(free_all(&list_token, &env), ERROR);
	// print_env(env);
	config_minishell_signal();
	while (1)
	{
		input = readline("Minishell > ");
		if (!input || ft_strlen(input) <= 0 || space_only(input) == 0)
			break ;//malloc readline error
		else
		{
			add_history(input); // Ajoute l'entrée à l'historique de readline pour qu'elle puisse être rappelée avec les flèches du clavier.
			if (parsing(input, &list_token) == ERROR) // Appelle la fonction parsing pour analyser l'entrée et stocker les jetons dans list_token.
				return (free_all(&list_token, &env), ERROR);			  // Quitte le programme avec le code de retour 1 (erreur) si la fonction parsing retourne 1.
			print_token(list_token);
			expand(&list_token, &env);
			if (list_token->next || list_token->str)
				if (execution(list_token, &env) == 1)
			// 		return 1;
			print_token(list_token);
		}
		free_list_token(&list_token);
		free_list_token(&list_token);
	}
	free_all(&list_token, &env);
	rl_clear_history();
	write(STDOUT_FILENO, "exit\n", 5);
	return (SUCCESS);
}
