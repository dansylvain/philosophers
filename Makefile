# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dan <dan@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 05:50:42 by dsylvain          #+#    #+#              #
#    Updated: 2024/03/28 00:55:01 by dan              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -g -Iincludes/ -pthread -Wall -Wextra -Werror

# Source files
SRC =	src/main.c \
		src/check_input.c \
		src/utils.c \
		src/utils_2.c \
		src/filo_routine.c \
		src/create_and_initialize_data.c \
		src/time_related_utils.c \
		
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)
	@echo "\033[0;32mCompilation successful\033[0m"

%.o: %.c
	@printf "%-80s" $<
	@{ $(CC) $(CFLAGS) -I/usr/include -O3 -c $< -o $@; } 2>&1 || \
		(echo "\033[0;31mCompilation of $< failed\033[0m"; exit 1)
	@echo "\033[0;32mcompiled\033[0m"

clean:
	@rm	-f	$(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm	-f	$(NAME) $(NAME_BONUS)
	
re:	fclean	all	

.PHONY: all clean fclean re
