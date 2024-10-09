# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 19:29:05 by jmafueni          #+#    #+#              #
#    Updated: 2024/10/09 22:28:36 by jmafueni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

SRC = $(SRC_DIR)/init.c $(SRC_DIR)/philo.c $(SRC_DIR)/utils.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c |$(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rmdir $(OBJ_DIR) 2>/dev/null || true

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


