NAME = cub3D

BONUS = cub3D_bonus

CC = cc
CFLAGS = -MMD -MP -g -Wall -Wextra -Werror -I/usr/include -Iinc -Iinc_bonus -Imlx_linux -O3
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

SRC_DIR = ./src/
SRC_BON_DIR = ./src_bonus/
OBJ_DIR = ./obj/
OBJ_BON_DIR = ./obj_bonus/
INC_DIR = ./inc/
INC_BON_DIR = ./inc_bonus/
LIB_DIR = ./mlx_linux/
LIB_REPO = https://github.com/42Paris/minilibx-linux

SRC = $(shell find $(SRC_DIR) -name "*.c")
SRC_BON = $(shell find $(SRC_BON_DIR) -name "*.c")
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_BON = $(patsubst $(SRC_BON_DIR)%.c, $(OBJ_BON_DIR)%.o, $(SRC_BON))
DEP = $(OBJ:%.o=%.d)
DEP_BON = $(OBJ_BON:%.o=%.d)

HEADER = $(wildcard $(INC_DIR)*.h)
HEADER_BON = $(wildcard $(INC_BON_DIR)*.h)
LIB = $(LIB_DIR)libmlx.a

all: $(LIB) $(NAME)

bonus: $(LIB) $(BONUS)

clean: 
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BON_DIR)
	@echo "clean done"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)
	@rm -rf $(LIB_DIR)
	@echo "fclean done"

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) done"

$(BONUS): $(OBJ_BON)
	$(CC) $(OBJ_BON) $(MLX_FLAGS) -o $(BONUS)
	@echo "$(BONUS) done"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BON_DIR)%.o: $(SRC_BON_DIR)%.c $(HEADER_BON) $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@mkdir -p $(LIB_DIR)
	@if [ ! -d "$(LIB_DIR).git" ]; then \
		git clone $(LIB_REPO) $(LIB_DIR); \
		echo "Library cloned in $(LIB_DIR)"; \
	fi
	@$(MAKE) -C $(LIB_DIR)

.PHONY: all, clean, fclean, re
