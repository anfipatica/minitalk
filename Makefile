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
PRINTF = ./ft_printf/ft_printf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

RM = rm -rf


.PHONY: all clean fclean re

all: $(SERVER) $(CLIENT)


$(SERVER): objs $(OBJS_DIR)server.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LIBFT) $(PRINTF) $(OBJS_DIR)server.o -o $(BIN_DIR)$(SERVER)

$(CLIENT): $(OBJS_DIR)client.o
	$(CC) $(CFLAGS) $(LIBFT) $(PRINTF) $(OBJS_DIR)client.o -o $(BIN_DIR)$(CLIENT)

objs:
	mkdir -p $(OBJS_DIR)
	make re -C ft_printf
	make re -C libft

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@

bonus: server_bonus client_bonus

server_bonus: objs_bonus $(OBJS_BONUS_DIR)server_bonus.o
	$(CC) $(CFLAGS) $(OBJS_BONUS_DIR)server_bonus.o $(LIBFT) $(PRINTF) -o $(BIN_DIR)server_bonus

client_bonus: $(OBJS_BONUS_DIR)client_bonus.o
	$(CC) $(CFLAGS) $(OBJS_BONUS_DIR)client_bonus.o $(LIBFT) $(PRINTF) -o $(BIN_DIR)client_bonus

objs_bonus:
	mkdir -p $(OBJS_BONUS_DIR)
	mkdir -p $(BONUS_DIR)
	make re -C libft
	make re -C ft_printf

$(OBJS_BONUS_DIR)%.o: $(BONUS_DIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(BIN_DIR)

re: fclean all
