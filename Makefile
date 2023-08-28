# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audrye <audrye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/08/28 08:31:29 by audrye           ###   ########.fr        #
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


SRCS =			minishell.c							\
				$(UTILS_LOC)lib_utils.c				\
				$(UTILS_LOC)lib_utils2.c			\
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
				$(EXPAND_LOC)env_utils.c			\
				$(EXPAND_LOC)expand_word.c			\
				$(EXPAND_LOC)expand_dquotes.c		\
				$(EXPAND_LOC)expand_dquotes_utils.c	\
				$(EXPAND_LOC)env.c					\
				$(EXPAND_LOC)expand.c				\
				$(EXPAND_LOC)expand_utils.c			\
				$(EXEC_LOC)execution.c				\
				$(EXEC_LOC)utils_exe.c				\
				$(EXEC_LOC)utils_exe2.c				\
				$(EXEC_LOC)utils_exe3.c				\
				$(EXEC_LOC)utils_exe4.c				\
				$(EXEC_LOC)redir.c					\
				$(EXEC_LOC)pipe.c					\
				$(EXEC_LOC)/builtins/cmd_env.c		\
				$(EXEC_LOC)/builtins/echo.c

OBJS =			$(SRCS:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CREADLINE) -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean $(NAME)
