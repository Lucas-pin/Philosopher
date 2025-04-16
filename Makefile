# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 00:00:00 by lpin              #+#    #+#              #
#    Updated: 2025/04/16 22:08:37 by lpin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME = philo

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = header

# Source and object files
SRC_FILES = check_entry.c \
            error.c \
            main.c \
			memory_utils.c \
			monitor_routine.c \
			mutex.c \
			orchestor.c \
			philo_routine.c \
			philos.c \
            pthreads.c \
            pthread_utils.c \
            sincronization.c \
            table.c \
            utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Colors for messages
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Main rule
all: $(NAME)

# Rule to compile the executable
$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully compiled.$(RESET)"

# Rule to compile .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

# Clean everything (object files and executable)
fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)

# Recompile from scratch
re: fclean all

# Do not treat these rules as files
.PHONY: all clean fclean re