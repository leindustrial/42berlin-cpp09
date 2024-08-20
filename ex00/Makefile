# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ole <ole@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 09:48:33 by ole               #+#    #+#              #
#    Updated: 2024/02/22 12:34:02 by ole              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	btc

COLOR	=	\033[0;38;5;11m
RESET	=	\033[00m

SRCS	=	main.cpp \
			BitcoinExchange.cpp \

OBJS	=	$(SRCS:.cpp=.o)

CC		=	@c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98 -g

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME)
			@printf "\n$(COLOR)o-------------------------------------------o\n"
			@printf "$(COLOR)|$(RESET)                ! compiled !               $(COLOR)|\n"
			@printf "o-------------------------------------------o$(RESET)\n\n"

%.o:		%.cpp
			@$(CC) $(FLAGS) -o $@ -c $<

clean:		
			@rm -f $(OBJS)

fclean: 	clean
			@rm -f $(NAME)
			@printf "\n$(COLOR)------------ all are files deleted ----------$(RESET)\n\n"

re: 		fclean all
