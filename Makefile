# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 00:05:21 by hirosuzu          #+#    #+#              #
#    Updated: 2024/03/04 20:18:13 by hirosuzu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRCS	=	\
main.c	\
ft_strtol.c	\
ft_calloc.c \
check_error.c \
set_data.c \
func_order.c \
display_order.c \

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all clean

# main:
# 	cc -g -fsanitize=address *.c

.PHONY: all clean fclean re

