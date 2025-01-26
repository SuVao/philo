NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = ./src
OBJ_DIR = ./obj
SRC_FILES = philo.c				\
			math_utils.c		\
			cleaning_house.c	\
			utils.c				\
			init_table.c		\
			init_threads.c		\
			dinner.c			\
			checks.c			\
			set_get.c			\
			routines.c          \
			gamela.c            \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Regra para compilar cada arquivo .c em .o no diretório OBJ_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regras principais
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
