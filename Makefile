# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/07/26 23:07:05 by ntardy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			gcc

CREADLINE=		-lreadline

CFLAGS =		-Wall -Werror -Wextra

PARS_LOC =		parsing/
UTILS_LOC =		utils/
EXEC_LOC =		execution/


SRCS =			minishell.c							\
				$(UTILS_LOC)lib_utils.c				\
				$(UTILS_LOC)split.c					\
				$(UTILS_LOC)free.c					\
				$(PARS_LOC)parsing.c				\
				$(PARS_LOC)error.c					\
				$(PARS_LOC)fill.c					\
				$(PARS_LOC)fill_utils.c				\
				$(PARS_LOC)check_pars.c				\
				$(PARS_LOC)init.c					\
				$(EXEC_LOC)execution.c				\
				$(EXEC_LOC)utils_exe.c

OBJS =			$(SRCS:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CREADLINE) -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean $(NAME)
