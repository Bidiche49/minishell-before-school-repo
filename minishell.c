/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:11 by ntardy            #+#    #+#             */
/*   Updated: 2023/08/31 12:54:38 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_error;

void print_token(t_token *list_token)
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
	while(env)
	{
		if(!env->content)
			printf("%s\n", env->name);
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

int	parsing_expand(char *input, t_token **token, t_env **env)
{
	int		return_val;

	printf("parsing_expand\n");
	return_val = parsing(input, token);
	if (return_val == ERROR)
		return (free_all(input, token, env), ERROR);
	if (return_val == SUCCESS)
	{
		return_val = expand(token, env);
		if (return_val == ERROR)
			return (free_all(input, token, env), ERROR);
		if (return_val == SUCCESS)
			return (SUCCESS);
	}
	return (NEW_LINE);
}

int main(int argc, char **argv, char **envd)
{
	int		return_val;
	char	*input;
	t_token	*list_token;
	t_env	*env;

	if (argc != 1)
		return (msg(ERR_MANY_ARG), ERROR);
	if (!envd)
		return (msg(ERR_ENV_KO), ERROR);
	input = NULL;
	list_token = NULL;
	env = NULL;
	(void)argv;
	if (create_env(envd, &env) == ERROR)
		return(free_all(input, &list_token, &env), ERROR);
	config_minishell_signal();
	while (input == NULL || ft_strcmp(input, "stop"))
	{
		input = readline(BOLD CYAN "Minishell > " RESET);
		if (!input || ft_strlen(input) <= 0 || space_only(input))
			break ;//malloc readline error
		else
		{
			add_history(input);
			return_val = parsing_expand(input, &list_token, &env);
			if (return_val == ERROR)
				return(free_all(input, &list_token, &env), ERROR);
			if (return_val == SUCCESS)
			{
					print_token(list_token);
					if (execution(list_token, &env) == ERROR)
						return (ERROR);
			}
		}
		free_list_token(&list_token);
	}
	free_all(input, &list_token, &env);
	rl_clear_history();
	printf(BOLD GREEN "exit\n" RESET);
	return (g_error);
}


//make && valgrind --leak-check=full --show-leak-kinds=all --suppressions=minishell.supp ./minishell
