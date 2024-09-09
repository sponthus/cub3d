NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

HEADER = $(wildcard *.h)

all: $(NAME)

clean: 
	rm -rf $(OBJ_DIR)
	@echo "clean done"

fclean: clean
	rm -rf $(NAME)
	@echo "fclean done"

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
	@echo "$(NAME) done"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all, clean, fclean, re
