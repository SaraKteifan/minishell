NAME = libft.a

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

FILES = ft_strlen \
			 ft_memmove \
			 ft_memcpy \
			 ft_strlcpy \
			 ft_strlcat \
			 ft_isalpha \
			 ft_isdigit \
			 ft_isalnum \
			 ft_isascii \
			 ft_isprint \
			 ft_memset \
			 ft_bzero \
			 ft_toupper \
			 ft_tolower \
			 ft_strchr \
			 ft_strrchr \
			 ft_strncmp \
			 ft_memchr \
			 ft_memcmp \
			 ft_strnstr \
			 ft_atoi \
			 ft_calloc \
			 ft_strdup \
			 ft_substr \
			 ft_strjoin \
			 ft_split \
			 ft_putchar_fd \
			 ft_putstr_fd \
			 ft_putendl_fd \
			 ft_putnbr_fd \
			 ft_strmapi \
			 ft_striteri \
			 ft_itoa \
			 ft_strtrim

BFILES = ft_lstnew_bonus \
			 ft_lstadd_front_bonus \
			 ft_lstsize_bonus \
			 ft_lstlast_bonus \
			 ft_lstadd_back_bonus \
			 ft_lstdelone_bonus \
			 ft_lstclear_bonus \
			 ft_lstiter_bonus \
			 ft_lstmap_bonus

CFILES = $(FILES:%=%.c)

BCFILES = $(BFILES:%=%.c)

OFILES = $(FILES:%=%.o)

BOFILES = $(BFILES:%=%.o)

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(NAME): $(OFILES)
	ar -rcs $(NAME) $(OFILES)

all: $(NAME)

bonus: $(BOFILES) $(NAME)
	ar -rcs $(NAME) $(BOFILES)

clean:
	rm -f $(OFILES) $(BOFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
