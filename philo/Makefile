# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 19:29:05 by jmafueni          #+#    #+#              #
#    Updated: 2024/11/13 20:05:36 by jmafueni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj/

SRC = $(SRC_DIR)/init.c $(SRC_DIR)/philo.c $(SRC_DIR)/check_philo.c $(SRC_DIR)/routine.c \
	$(SRC_DIR)/utils.c  $(SRC_DIR)/ft_atol.c  $(SRC_DIR)/input_check.c $(SRC_DIR)/eat.c\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread  -g3

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c |$(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;31m======== philo object files removed ========\033[0m"

fclean:clean
	@rm -f $(NAME)
	@echo "\033[1;31m======= philo executable removed =======\033[0m"

re: fclean all

.PHONY: all clean fclean re


