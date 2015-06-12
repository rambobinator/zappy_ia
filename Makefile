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

SRC = main.cpp Buffer.cpp Client.cpp Icmd.cpp Inventory.cpp Messages.cpp \
	utils.cpp Map.cpp Coop.cpp Ia.cpp Ia_alone.cpp Ia_feeder.cpp Ia_mother.cpp \
	Ia_picker.cpp

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	g++ -o $@ $^ -Wall -Wextra -Werror -g -std=c++11

%.o: %.c
	g++ -c $^ -o $@ -Wall -Wextra -Werror -g -std=c++11

clean:
	rm -rf $(SRC:.cpp=.o)

fclean: clean
	rm -rf $(NAME)

re: fclean all
