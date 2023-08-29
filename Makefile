# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/08/29 15:26:14 by ntardy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			gcc

CREADLINE=		-lreadline

CFLAGS =		-Wall -Werror -Wextra -g3

PARS_LOC =		parsing/
UTILS_LOC =		utils/
EXEC_LOC =		execution/
BUILTINS_LOC =	$(EXEC_LOC)builtins/
EXPAND_LOC =	expand/
ENV_LOC =		env/

# Couleurs
RESET   = \033[0m
GREEN   = \033[32m
RED     = \033[31m
YELLOW  = \033[33m
CYAN    = \033[36m

SRCS =			minishell.c							\
				$(UTILS_LOC)lib_utils.c				\
				$(UTILS_LOC)lib_utils2.c			\
				$(UTILS_LOC)lib_utils3.c			\
				$(UTILS_LOC)split.c					\
				$(UTILS_LOC)free.c					\
				$(UTILS_LOC)signal.c				\
				$(PARS_LOC)parsing.c				\
				$(PARS_LOC)pars_utils.c				\
				$(PARS_LOC)operator_mod.c			\
				$(PARS_LOC)error.c					\
				$(PARS_LOC)fill.c					\
				$(PARS_LOC)fill_utils.c				\
				$(PARS_LOC)init.c					\
				$(ENV_LOC)env_utils.c				\
				$(ENV_LOC)env.c						\
				$(EXPAND_LOC)expand_word.c			\
				$(EXPAND_LOC)expand_dquotes.c		\
				$(EXPAND_LOC)expand_dquotes_utils.c	\
				$(EXPAND_LOC)expand.c				\
				$(EXPAND_LOC)expand_utils.c			\
				$(EXEC_LOC)execution.c				\
				$(EXEC_LOC)utils_exe.c				\
				$(EXEC_LOC)utils_exe2.c				\
				$(EXEC_LOC)utils_exe3.c				\
				$(EXEC_LOC)utils_exe4.c				\
				$(EXEC_LOC)redir.c					\
				$(EXEC_LOC)pipe.c					\
				$(BUILTINS_LOC)cmd_env.c			\
				$(BUILTINS_LOC)export.c				\
				$(BUILTINS_LOC)export_utils.c		\
				$(BUILTINS_LOC)unset.c				\
				$(BUILTINS_LOC)echo.c

OBJS =			$(SRCS:.c=.o)

# Options de compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
CREADLINE = -lreadline

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling in progress...$(RESET)"
	@{ $(CC) $(CFLAGS) $(OBJS) $(CREADLINE) -o $(NAME) || \
		(echo "$(RED)Compilation failed.$(RESET)"; exit 1)}
	@echo -n "$(GREEN)[                    ]$(RESET)"
	@echo -n "\r$(GREEN)[=>                  ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[===>                ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[=====>              ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[========>           ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[===========>        ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[==============>     ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[==================>  ]$(RESET)"
	@sleep 0.1
	@echo "\r$(GREEN)[=====================$(RESET)"
	@echo "$(GREEN)Compilation completed.$(RESET)"
	@echo "$(CYAN)          _____    __ ____   __          __  __    __  $(RESET)"
	@echo "$(CYAN)  /\/\    \_  _\/\ \ \\_  _\ / __\ /\  /\/__\/ /   / /  $(RESET)"
	@echo "$(CYAN) /    \    / / /  \/ / / /  \ \  / /_/ /_\ / /   / /   $(RESET)"
	@echo "$(CYAN)/ /\/\ \/\/ /_/ /\  /\/ /_ __\ \/ __  //__/ /___/ /___ $(RESET)"
	@echo "$(CYAN)\/    \/\____/\_\ \/\____/ \___/\/ /_/\__/\____/\____/ $(RESET)"
	@echo "$(CYAN)                                                       $(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null


clean:
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@echo -n "$(GREEN)[                    ]$(RESET)"
	@rm -f $(OBJS)
	@echo -n "\r$(GREEN)[=>                  ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[===>                ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[=====>              ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[========>           ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[===========>        ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[==============>     ]$(RESET)"
	@sleep 0.1
	@echo -n "\r$(GREEN)[==================>  ]$(RESET)"
	@sleep 0.1
	@echo "\r$(GREEN)[=====================$(RESET)"
	@echo "$(GREEN)Object files removed.$(RESET)"

fclean: clean
	@sleep 0.1
	@echo "$(YELLOW)Removing the executable...$(RESET)"
	@rm -f $(NAME)
	@sleep 0.1
	@echo "$(GREEN)Executable removed.$(RESET)"

re: fclean all
