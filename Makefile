CC = cc
CFLAGS = -I/opt/homebrew/opt/readline/include -Wall -Wextra -Werror -I. 
DEBUG_FLAGS = -g

NAME = minishell

SRC = minishell.c  utils.c ft_tokenize.c parsing.c ft_reader.c builtins/builtins.c quote_chk.c esc_seq.c builtins/ft_echo.c  \
	Dolar_expand/dollar_expand.c Dolar_expand/dollar_utils.c  builtins/ft_pwd.c builtins/ft_cd.c  builtins/ft_exit.c redirection.c builtins/ft_env.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

RL_LIB = -L/opt/homebrew/opt/readline/lib -lreadline

all: $(NAME) 

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJ) $(LIBFT) $(RL_LIB) -o $(NAME) 
	rm -f $(OBJ)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re