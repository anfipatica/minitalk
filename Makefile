SERVER = $(BIN_DIR)server
CLIENT = $(BIN_DIR)client
BONUS_SERVER = server_bonus
BONUS_CLIENT = client_bonus

INC_DIR = ./inc
OBJS_DIR = ./obj/
OBJS_BONUS_DIR = ./obj/bonus/
BIN_DIR = ./bin/
SRC_DIR = ./src/
BONUS_DIR = ./bonus/
LIBFT = ./libft/libft.a
PRINTF = ./ft_printf/ft_printf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 -I$(INC_DIR)

RM = rm -rf

.PHONY: all clean fclean re

all: $(SERVER) $(CLIENT)

$(SERVER):$(OBJS_DIR)server.o
	mkdir -p $(BIN_DIR)
	make -C libft
	make -C ft_printf
	$(CC) $(CFLAGS) $(OBJS_DIR)server.o $(LIBFT) $(PRINTF) -o $(SERVER)

$(CLIENT): $(OBJS_DIR)client.o
	$(CC) $(CFLAGS) $(OBJS_DIR)client.o $(LIBFT) $(PRINTF) -o $(CLIENT)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus: $(BIN_DIR)server_bonus $(BIN_DIR)client_bonus

$(BIN_DIR)server_bonus: $(OBJS_BONUS_DIR)server_bonus.o
	make -C libft
	make -C ft_printf
	$(CC) $(CFLAGS) $(OBJS_BONUS_DIR)server_bonus.o $(LIBFT) $(PRINTF) -o $(BIN_DIR)server_bonus

$(BIN_DIR)client_bonus: $(OBJS_BONUS_DIR)client_bonus.o
	$(CC) $(CFLAGS) $(OBJS_BONUS_DIR)client_bonus.o $(LIBFT) $(PRINTF) -o $(BIN_DIR)client_bonus

$(OBJS_BONUS_DIR)%.o: $(BONUS_DIR)%.c
	mkdir -p $(OBJS_BONUS_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(BIN_DIR)

re: fclean all

