NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
LIB_DIR = ./mlx/
LIB_REPO = https://github.com/42Paris/minilibx-linux

SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
HEADER = $(wildcard $(INC_DIR)*.h)

all: $(LIB_DIR) $(NAME)

clean: 
	rm -rf $(OBJ_DIR)
	@echo "clean done"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB_DIR)
	@echo "fclean done"

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
	@echo "$(NAME) done"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)
	@git clone $(LIB_REPO) $(LIB_DIR)
	@echo "Library cloned in $(LIB_DIR)"

.PHONY: all, clean, fclean, re
