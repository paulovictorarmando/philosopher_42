# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgomes <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 10:33:55 by parmando          #+#    #+#              #
#    Updated: 2025/02/13 12:32:10 by pgomes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	main.c\
	get_args.c\
	controller.c\
	simulation.c\
	funcs.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re: fclean all
