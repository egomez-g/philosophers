# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 17:50:58 by egomez-g          #+#    #+#              #
#    Updated: 2024/02/18 14:55:34 by egomez-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra 

NAME = philo

SRCS =	main.c						\
		sources/threads.c			\
		sources/atoi_philo.c		\
		sources/utils.c				\
		sources/eat_sleep_think.c	\
		sources/parse.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

clear:
	@clear

run: clear re
	@./$(NAME) 4 500 200 100 1

.PHONY: clean fclean re