SERVER = server
CLIENT = client
BONUS_SERVER = server_bonus
BONUS_CLIENT = client_bonus


OBJS_DIR = ./obj/
OBJS_BONUS_DIR = ./obj/bonus/
BIN_DIR = ./bin/
SRC_DIR = ./src/
BONUS_DIR = ./bonus/
LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall

RM = rm -rf


.PHONY: all clean fclean re

all: $(SERVER)


$(SERVER): objs $(OBJS_DIR)server.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLssAGS) $(OBJS_DIR)server.o $(LIBFT) -o $(BIN_DIR)$(SERVER)

objs:
	mkdir -p $(OBJS_DIR)
	make -C libft

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $(LIBFT) $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(BIN_DIR)

re: fclean all