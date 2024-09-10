NAME = cub3d

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I/usr/include -Iinc -Imlx_linux -O3
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
LIB_DIR = ./mlx_linux/
LIB_REPO = https://github.com/42Paris/minilibx-linux

SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
HEADER = $(wildcard $(INC_DIR)*.h)
LIB = $(LIB_DIR)libmlx.a

all: $(LIB) $(NAME)

clean: 
	rm -rf $(OBJ_DIR)
	@echo "clean done"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB_DIR)
	@echo "fclean done"

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) done"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(LIB)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@mkdir -p $(LIB_DIR)
	@if [ ! -d "$(LIB_DIR).git" ]; then \
		git clone $(LIB_REPO) $(LIB_DIR); \
		echo "Library cloned in $(LIB_DIR)"; \
	fi
	@$(MAKE) -C $(LIB_DIR)

.PHONY: all, clean, fclean, re
