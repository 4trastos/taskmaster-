NAME = taskmaster
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -Iincl
RM = rm -f
LIB = -lftprintf

SRC = src/main.c src/config.c src/logger.c src/process.c src/shell.c src/signal_handler.c aux/auxiliar.c
OBJS = $(SRC:.c=.o)

FT_PRINTF_DIR = lib/printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(FT_PRINTF_DIR) $(LIB) -lm

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C $(FT_PRINTF_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re $(FT_PRINTF)