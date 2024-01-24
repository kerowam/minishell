#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RESET		"\x1B[0m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"

typedef struct s_prompt
{
	char	**envp;
	pid_t	pid;
	int		g_status;
}				t_prompt;

//builtins.c
int			env_command(char **envp);
int			pwd_command(void);
int			echo_command(char **args);
int			unset_command_with_args(char **args, char ***envp);
int			unset_command(char **args, char ***envp);

//builtins2.c
char		*update_variable(char *variable, char *new_value);
void		update_pwd(char ***envp, char *new_pwd);
void		cd_command(char *path, char ***envp);

//main.c
void		ft_header(void);
void		run_shell(char **env);
void		process_line(char *line, char ***env);
int			main(int argc, char **argv, char **env);
void		ft_leaks(void);

//utils.c
void		free_str_array(char **str_array);

//cd_utils.c
int			get_int_length(int value);
void		int_to_str(char *buffer, int value);
size_t		handle_percent(char *buffer, int *j, char *format, void *args[]);
size_t		handle_string(char *buffer, int *j, char *str);
int			my_sprintf(char *buffer, char *format, void *args[]);

#endif