# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 15:17:48 by josemigu          #+#    #+#              #
#    Updated: 2025/10/29 16:20:18 by josemigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME		= philo

# Compiler
CC				= cc
CFLAGS			= -Werror -Wextra -Wall -g
CFLAGS_SANITIZE	= -Wall -Wextra -Werror -g -L. -lpthread -g3 -fsanitize=thread -O3 -march=native

# Includes
INC			=	-I ./

# Sources
SRC_PATH	=	./
SRC			=	philo.c init.c utils.c simulation.c monitor.c get_set.c \
				fork_ops.c mutexes.c get_set2.c

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

sanitize: $(OBJS)
	@echo "Compiling philo with sanitizers..."
	$(CC) $(CFLAGS_SANITIZE) -o $(NAME) $(OBJS) $(INC)
	@echo "✅ Philo compiled with sanitize flags!!!"

helgrind: $(OBJS)
	@echo "Compiling philo with valgrind..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "✅ Philo compiled to run with helgrind!!!"

.PHONY: all re clean fclean
