NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../../incl
RM = rm -f

SRCS = ft_printf.c ft_printf_char.c ft_printf_numbers.c
OBJS = $(SRCS:.c=.o)

LIB = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(LIB) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
