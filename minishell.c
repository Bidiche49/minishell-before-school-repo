/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/06 02:47:58 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_error;

void	print_token(t_token *list_token)
{
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
	while (env)
	{
		if (!env->content)
			printf("%s\n", env->name);
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}

int	main_loop(char *input, t_token **token, t_env **env)
{
	int	return_val;

	config_minishell_signal();
	while (1)
	{
		input = readline("\001" BOLD CYAN "\002" "Minishell > " "\001" RESET "\002");
		if (!input)
			break ;
		else if (ft_strlen(input) > 0 && !space_only(input))
		{
			add_history(input);
			return_val = parsing(input, token, env);
			if (return_val == ERROR)
				return (free_all(input, token, env), ERROR);
			print_token(*token);
			if (return_val == SUCCESS)
				if (execution(*token, env) == ERROR)
					return (ERROR);
		}
		free_all(input, token, NULL);
	}
	return (SUCCESS);
}

int	end_funct(char *input, t_token **token, t_env **env)
{
	free_all(input, token, env);
	rl_clear_history();
	printf(BOLD GREEN "exit\n" RESET);
	return (g_error);
}

int	main(int argc, char **argv, char **envd)
{
	char			*input;
	t_token			*token;
	static t_env	*env = NULL;

	input = NULL;
	token = NULL;
	if (argc != 1)
		return (msg(ERR_MANY_ARG), ERROR);
	if (!envd)
		return (msg(ERR_ENV_KO), ERROR);
	if (create_env(envd, &env) == ERROR)
		return (free_all(input, &token, &env), ERROR);
	if (main_loop(input, &token, &env) == ERROR)
		return (free_all(input, &token, &env), g_error);
	return ((void)argv, end_funct(input, &token, &env));
}

//make && valgrind --leak-check=full --show-leak-kinds=all --suppressions=minishell.supp ./minishell
