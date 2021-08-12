# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/12 16:46:16 by pyasuko           #+#    #+#              #
#    Updated: 2021/08/12 17:28:42 by pyasuko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

HEADER =	philo.h

SRCS =		cycle.c \
			init.c \
			lib.c \
			message.c \
			monitor.c \
			parser.c \
			philo.c \
			utils.c

CFLAGS =	-Wall -Wextra -Werror

OBJ =		$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			@gcc $(OBJ) -o $(NAME)

clean:
			@rm -f $(OBJ)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re