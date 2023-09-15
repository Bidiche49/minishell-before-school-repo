# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/09/15 20:51:24 by ntardy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
CC					=	gcc

#*********************************#
#*             FLAGS             *#
#*********************************#
CFLAGS				=	-Wall -Werror -Wextra -g3
CREADLINE			=	-lreadline
VALGRIND_OPTIONS	=	--leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --track-origins=yes --suppressions=minishell.supp

#*********************************#
#*          PATH_FILES           *#
#*********************************#
PARS_PATH =		parsing/
UTILS_PATH =	utils/
ERROR_PATH =	$(UTILS_PATH)error/
GARBAGE_PATH =	$(UTILS_PATH)garbages_collector/
EXEC_PATH =		execution/
BUILTINS_PATH =	$(EXEC_PATH)builtins/
EXPAND_PATH =	expand/
ENV_PATH =		env/
EXPORT_PATH =	$(BUILTINS_PATH)export/
UNSET_PATH =	$(BUILTINS_PATH)unset/

#*********************************#
#*             FILES             *#
#*********************************#
FILES_UTILS =	$(UTILS_PATH)atoi.c					\
				$(UTILS_PATH)free.c					\
				$(UTILS_PATH)utils.c				\
				$(UTILS_PATH)split.c				\
				$(ERROR_PATH)error.c				\
				$(ERROR_PATH)error2.c				\
				$(UTILS_PATH)signal.c				\
				$(UTILS_PATH)ft_itoa.c				\
				$(UTILS_PATH)ft_calloc.c			\
				$(UTILS_PATH)utils_str.c			\
				$(UTILS_PATH)utils_malloc_str.c		\
				$(GARBAGE_PATH)garbage_fd.c			\
				$(GARBAGE_PATH)garbage_collector.c

FILES_PARS =	$(PARS_PATH)fill.c					\
				$(PARS_PATH)parsing.c				\
				$(PARS_PATH)fill_utils.c			\
				$(PARS_PATH)pars_utils.c			\
				$(PARS_PATH)operator_mod.c			\
				$(PARS_PATH)ft_strlen_remake.c

FILES_ENV =		$(ENV_PATH)env.c					\
				$(ENV_PATH)env_utils.c

FILES_EXPAND =	$(EXPAND_PATH)expand.c				\
				$(EXPAND_PATH)clean_token.c			\
				$(EXPAND_PATH)expand_word.c			\
				$(EXPAND_PATH)expand_utils.c		\
				$(EXPAND_PATH)expand_dquotes.c		\
				$(EXPAND_PATH)is_token_clean.c		\
				$(EXPAND_PATH)check_is_expand.c		\
				$(EXPAND_PATH)expand_dquotes_utils.c

FILES_EXEC =	$(EXEC_PATH)exec.c					\
				$(EXEC_PATH)open.c					\
				$(EXEC_PATH)heredoc.c				\
				$(EXEC_PATH)builtins.c				\
				$(EXEC_PATH)find_path.c				\
				$(EXEC_PATH)execution.c				\
				$(EXEC_PATH)init_section.c

FILES_BUILTIN =	$(UNSET_PATH)unset.c				\
				$(UNSET_PATH)unset_var.c			\
				$(EXPORT_PATH)export.c				\
				$(EXPORT_PATH)export_sort.c			\
				$(EXPORT_PATH)export_utils.c		\
				$(BUILTINS_PATH)exit.c				\
				$(BUILTINS_PATH)echo.c				\
				$(BUILTINS_PATH)env.c

SRCS =			minishell.c							\
				$(FILES_ENV)						\
				$(FILES_PARS)						\
				$(FILES_EXEC)						\
				$(FILES_UTILS)						\
				$(FILES_EXPAND)						\
				$(FILES_BUILTIN)					\
				$(UTILS_PATH)print_struct.c

OBJS =			$(SRCS:.c=.o)

#*********************************#
#*            COLORS             *#
#*********************************#
RESET	= \033[0m
GREEN	= \033[32m
RED		= \033[31m
YELLOW	= \033[33m
CYAN	= \033[36m

#*********************************#
#*           COMMANDS            *#
#*********************************#
.PHONY: all clean fclean re valgrind

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

valgrind: all
	@echo "$(YELLOW)Running minishell with valgrind...$(RESET)"
	@valgrind $(VALGRIND_OPTIONS) ./$(NAME)
