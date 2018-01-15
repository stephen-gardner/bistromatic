#!/usr/bin/make -f
NAME = calc
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I inc -I libft/inc
LIBFT = libft/libft.a
SRC_DIR = src
SRC = \
	arith_add\
	arith_div\
	arith_mul\
	arith_sub\
	fsm\
	fsm_eval\
	fsm_num\
	fsm_push\
	fsm_unary\
	main\
	num\
	util
OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Building $@..."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $@
	@echo "Done."

$(LIBFT):
	@echo "Building $@..."
	@make -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "$(NAME) removed."

re: fclean all
