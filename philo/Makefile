# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 15:17:48 by josemigu          #+#    #+#              #
#    Updated: 2025/10/25 21:01:12 by josemigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME		= philo

# Compiler
CC				= cc
CFLAGS			= -Werror -Wextra -Wall -g

# Includes
INC			=	-I ./

# Sources
SRC_PATH	=	./
SRC			=	philo.c init.c utils.c simulation.c monitor.c get_set.c \
				fork_ops.c mutexes.c

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	@echo "Compiling philo..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "✅ Philo compiled!!!"

clean:
	@echo "Removing .o object files..."
	rm -rf $(OBJ_PATH)

fclean: clean
	@echo "Removing binaries..."
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
