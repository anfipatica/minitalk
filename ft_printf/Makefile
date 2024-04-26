NAME = ft_printf.a

RM = rm -f 

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJS_DIR = ./obj

SRCS = ft_printf.c \
		printf_numbers.c

OBJS = $(SRCS:%.c=obj/%.o)

.PHONY: clean all fclean re

all: $(NAME)

$(NAME): objs $(OBJS)
	ar rcs $(NAME) $(OBJS)

objs:
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
