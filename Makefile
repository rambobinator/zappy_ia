# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/20 13:38:52 by brehaili          #+#    #+#              #
#    Updated: 2015/04/20 13:38:55 by brehaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client

SRC = main.cpp Buffer.cpp Client.cpp Icmd.cpp Inventory.cpp Map.cpp

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	g++ -o $@ $^ -Wall -Wextra -Werror -g -std=c++11

%.o: %.c
	g++ -c $^ -o $@ -Wall -Wextra -Werror -g -std=c++11

clean:
	rm -rf $(SRC:.c=.o) $(SRC2:.c=.o)

fclean: clean
	rm -rf $(NAME) $(NAME2)

re: fclean all