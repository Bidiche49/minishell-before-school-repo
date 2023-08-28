# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/08/29 00:11:08 by ntardy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			gcc

CREADLINE=		-lreadline

CFLAGS =		-Wall -Werror -Wextra -g3

PARS_LOC =		parsing/
UTILS_LOC =		utils/
EXEC_LOC =		execution/
EXPAND_LOC =	expand/
ENV_LOC =		env/

# Couleurs
RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m

SRCS =			minishell.c							\
				$(UTILS_LOC)lib_utils.c				\
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
				$(EXEC_LOC)redir.c

OBJS =			$(SRCS:.c=.o)

# Options de compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
CREADLINE = -lreadline

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling in progress...$(RESET)"
	@echo -n "$(GREEN)[                    ]$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(CREADLINE) -o $(NAME)
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

