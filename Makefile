NAME = minishell

CFLAGS = -g -Wextra -Wall -Werror
LIBFT = ./libft

SRCS = main.c\
		builtins.c\
		builtins2.c\
		utils.c\

CC = gcc

OBJS = ${SRCS:.c=.o}

all: ${LIBFT}/libft.a $(NAME)

$(NAME): $(OBJS)
	@$(CC) -g $(CFLAGS) ${LIBFT}/libft.a $(OBJS) -o $(NAME) -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(LIBFT)/libft.a:
	@${MAKE} -C ${LIBFT}

clean:
	@rm -rf $(OBJS)
	@${MAKE} -C ${LIBFT} clean

fclean: clean
	@rm -rf $(NAME)
	@${MAKE} -C ${LIBFT} fclean

re: fclean all

.PHONY: all, clean, fclean, re