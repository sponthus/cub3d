NAME = cub3d

CC = c
CFLAGS = -Wall -Wextra -Werror

SRC = $(wildcard *.c)

OBJ_DIR = ./OBJ/

OBJ = $(SRC:%.cpp=$(OBJ_DIR)%.o)

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

$(OBJ_DIR)%.o: %.cpp $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all, clean, fclean, re
