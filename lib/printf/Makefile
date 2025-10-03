NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS	=  ft_printf.c ft_printf_char.c ft_printf_numbers.c

LIB = ar rcs

OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):    $(OBJS)
	$(CC) -c $(CFLAGS) $(SRCS)
	$(LIB) $(NAME) $(OBJS)

clean:			
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
