NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRC_PATH    = src/
OBJ_PATH    = build/
INCLUDE     = include/
LIBFT_PATH  = lib/libft/

LIBFT          = $(LIBFT_PATH)libft.a
LIBFT_FLAGS    = -L$(LIBFT_PATH) -lft
READLINE_FLAGS = -lreadline -lncurses

SRC_FILES   = main init utils \
			env env_utils env_manage \
			lexer lexer_utils lexer_tokens lexer_handlers \
			expander expander_utils \
			parser parser_syntax parser_redir parser_args\
			cleanup
SRC         = $(addprefix $(SRC_PATH), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_PATH), $(addsuffix .o, $(SRC_FILES)))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $(OBJ) $(LIBFT_FLAGS) $(READLINE_FLAGS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | build
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory

build:
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
