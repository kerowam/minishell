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
		parser.c\
		lexer.c\
		lexer_utils.c\
		lexer_pipes.c\
		lexer_pipes_utils.c\
		lexer_redir.c\
		lexer_redir_utils.c\
		expander.c\
		expander_utils.c\
		quotes.c\
		quote_cleaner.c\
		error.c\
		executor.c\
		utils2.c\
		executor_utils.c\
		utils3.c\
		executor_utils2.c\
		redirections.c\
		here_doc.c\
		free.c\
		parser_utils.c\
		parser_utils2.c\
		here_doc_utils.c\

CC = gcc

OBJS = ${SRCS:.c=.o}

all: ${LIBFT}/libft.a $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(SRCS) ${LIBFT}/libft.a -o $(NAME) -lreadline
	
#gcc -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline main.c -o main

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