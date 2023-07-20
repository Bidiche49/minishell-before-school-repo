# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:59:08 by ntardy            #+#    #+#              #
#    Updated: 2023/07/20 19:16:36 by ntardy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

NAME_BONUS =	so_long_bonus

CC =			gcc

CREADLINE=		-lreadline

CFLAGS =		-Wall -Werror -Wextra

PARS_LOC =		parsing/
UTILS_LOC =		utils/
EXEC_LOC =		exec/


SRCS =			minishell.c							\
				$(UTILS_LOC)lib_utils.c				\

OBJS =			$(SRCS:.c=.o)

# %.o: %.c
# 	$(CC)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CREADLINE)

.PHONY: clean
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

.PHONY: re
re: fclean $(NAME)
