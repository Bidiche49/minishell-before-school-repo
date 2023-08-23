# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/08/23 00:07:54 by ntardy           ###   ########.fr        #
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
				$(UTILS_LOC)split.c					\
				$(UTILS_LOC)free.c					\
				$(UTILS_LOC)signal.c				\
				$(PARS_LOC)parsing.c				\
				$(PARS_LOC)pars_utils.c				\
				$(PARS_LOC)operator_mod.c			\
				$(PARS_LOC)error.c					\
				$(PARS_LOC)fill.c					\
				$(PARS_LOC)fill_utils.c				\
				$(PARS_LOC)check_pars.c				\
				$(PARS_LOC)init.c					\
				$(EXPAND_LOC)env_utils.c			\
				$(EXPAND_LOC)env.c					\
				$(EXPAND_LOC)expand.c				\
				$(EXEC_LOC)execution.c				\
				$(EXEC_LOC)utils_exe.c				\
				$(EXEC_LOC)utils_exe2.c				\
				$(EXEC_LOC)utils_exe3.c				\
				$(EXEC_LOC)utils_exe4.c				\
				$(EXEC_LOC)redir.c

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
