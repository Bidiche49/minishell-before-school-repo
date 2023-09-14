/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/14 18:53:24 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_error;

void	print_token(t_token *list_token)
{
	t_token *tmp;

	tmp = list_token;
	while (tmp)
	{
		printf("[");
		if (tmp->type == WORD)
			printf("WORD");
		if (tmp->type == SEPARATOR)
			printf("SEPARATOR");
		if (tmp->type == D_QUOTES)
			printf("D_QUOTES");
		if (tmp->type == S_QUOTES)
			printf("S_QUOTES");
		if (tmp->type == OUT)
			printf("OUT");
		if (tmp->type == IN)
			printf("IN");
		if (tmp->type == HEREDOC)
			printf("HEREDOC");
		if (tmp->type == APPEND)
			printf("APPEND");
		if (tmp->type == PIPE)
			printf("PIPE");
		printf(" =");
		if (tmp)
			printf("%s", tmp->str);
		printf("] ");
		tmp = tmp->next;
	}
	printf("\n");
}

void	print_envd(char **env)
{
	int	i;

	i = 0;
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
				return (ERROR);
			print_token(*token);
			if (return_val == SUCCESS)
				if (execution(*token, env) == ERROR && g_error != EXIT)
					return (ERROR);
		}
		if (g_error == EXIT)
			return (g_error = SUCCESS, SUCCESS);
	}
	return (SUCCESS);
}

int	end_funct()
{
	close(0);
	close(1);
	close(2);
	garbage_collect();
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
		return (garbage_collect(), rl_clear_history(), g_error);
	if (main_loop(input, &token, &env) == ERROR)
		return (garbage_collect(), rl_clear_history(), g_error);
	return ((void)argv, end_funct());
}

//make && valgrind --leak-check=full --show-leak-kinds=all --suppressions=minishell.supp ./minishell
