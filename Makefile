# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/07/22 15:42:29 by ntardy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			gcc

CREADLINE=		-lreadline

CFLAGS =		-Wall -Werror -Wextra

PARS_LOC =		parsing/
UTILS_LOC =		utils/
EXEC_LOC =		exec/


SRCS =			minishell.c							\
				$(UTILS_LOC)lib_utils.c				\
				$(PARS_LOC)parsing.c				\
				$(PARS_LOC)error.c					\
				$(PARS_LOC)fill.c					\
				$(PARS_LOC)split.c					\
				$(PARS_LOC)fill_utils.c				\
				$(PARS_LOC)check_pars.c				\
				$(PARS_LOC)init.c

OBJS =			$(SRCS:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CREADLINE)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean $(NAME)
