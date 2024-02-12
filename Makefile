NAME = minishell

CFLAGS = -g -Wextra -Wall -Werror
LIBFT = ./libft

SRCS = main.c\
		enviroment.c\
		utils.c\
		builtins.c\
		cd_utils.c\
		cd.c\
		export_utils.c\
		parse.c\
		lexer.c\
		lexer_utils.c\
		lexer_pipes.c\
		lexer_pipes_utils.c\
		lexer_redir.c\
		lexer_redir_utils.c\
		expander.c\
		expander_utils.c\
		executor.c\


COMPILATION_DONE = no

CC = gcc

OBJS = ${SRCS:.c=.o}

all: ${LIBFT}/libft.a $(NAME) message

$(NAME): $(OBJS)
	@$(CC) -g $(CFLAGS) $(SRCS) ${LIBFT}/libft.a -o $(NAME) -lreadline
	@$(eval COMPILATION_DONE = yes)

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

message:
	@if [ "$(COMPILATION_DONE)" = "yes" ]; \
	then \
		echo "\033[92mCompilation completed successfully! 🚀\033[0m"; \
	else \
		echo "\033[93mNothing to be done. $(NAME) is up-to-date.\033[0m"; \
	fi


.PHONY: all, clean, fclean, re