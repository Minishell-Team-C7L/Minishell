NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g $(shell pkg-config --cflags readline)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCDIR = .
PARSING_DIR = parsing
TOKEN_DIR = token_it

SRCS = $(PARSING_DIR)/parse.c parsing/parse_utlis.c parsing/parse_utlis2.c \
       $(TOKEN_DIR)/handel_tokenizer.c $(TOKEN_DIR)/linerr.c $(TOKEN_DIR)/linemod.c \
       minishill.c

OBJS = $(SRCS:.c=.o)

TEST_SRCS = test_parsing.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft $(shell pkg-config --libs readline)

test: $(TEST_OBJS) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o test_parsing $(TEST_OBJS) $(OBJS) -L$(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) test_parsing
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test
