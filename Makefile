NAME = minishell

CFLAGS = -g -Wextra -Wall -Werror
LIBFT = ./libft
LEAK = ./memory-leaks

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
		free2.c\
		parser_utils3.c\
		quote_cleaner_utils.c\
		signals.c

CC = gcc

OBJS = ${SRCS:.c=.o}

all: ${LIBFT}/libft.a ${LEAKD}/memory_leaks.a $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(SRCS) ${LIBFT}/libft.a ${LEAK}/memory_leaks.a -lreadline -o $(NAME)

#	gcc $(CFLAGS) -lreadline -L/Users/gfredes-/.brew/opt/readline/lib -I/Users/gfredes-/.brew/opt/readline/include $(SRCS) ${LIBFT}/libft.a ${LEAK}/memory_leaks.a -o $(NAME)
	
#	@$(CC) $(CFLAGS) $(SRCS) ${LIBFT}/libft.a ${LEAK}/memory_leaks.a -o $(NAME) -lreadline
	

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(LIBFT)/libft.a:
	@${MAKE} -C ${LIBFT}

${LEAKD}/memory_leaks.a:
	@${MAKE} -C ${LEAK}

clean:
	@rm -rf $(OBJS)
	@${MAKE} -C ${LIBFT} clean

fclean: clean
	@rm -rf $(NAME)
	@${MAKE} -C ${LIBFT} fclean

re: fclean all

.PHONY: all, clean, fclean, re