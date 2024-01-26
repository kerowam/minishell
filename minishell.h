
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

# define Q		'\''
# define D_Q	'\"'

typedef struct s_mini
{
	char			**full_cmd;
	char			*full_path;
	int				infile;
	int				outfile;
	struct s_mini	*next;
}			t_mini;

typedef struct s_prompt
{
	t_mini	*cmds;
	char	**envp;
	pid_t	pid;
	int		g_status;
}				t_prompt;

//Para
typedef struct	s_process
{
	struct	t_process	*next;
	char				**argv;//Así o solo con 1 *???
	pid_t				pid;
	char				token;//?????
	int					completed;//?????
	int					stopped;//?????
	int					status;//????
}				t_process;

//Cada trabajo representa un proceso (Todo lo que hay dentro de un pipe)
typedef struct	s_job
{
	struct t_job	*next_job;
	char			*command;
	t_process		*first_process;
	pid_t			pid_group;//???
	int				infile;
	int				outfile;
	int				stderr;

}				t_job;

//builtins.c
int			env_command(char **envp);
int			pwd_command(void);
int			echo_command(char **args);
int			unset_command_with_args(char **args, char ***envp);
int			unset_command(char **args, char ***envp);

//builtins2.c
void		cd_command(char *path);
int			find_env_var(char **environ, char *name);
void		delete_env_var(char **environ, int index);
void		add_env_var(char **environ, char *new_var);
void		export_func(char ***environ, char *input);

//main.c
void		ft_header(void);
void		run_shell(char **env);
void		process_line(char *line, char ***env);
int			main(int argc, char **argv, char **env);
void		ft_leaks(void);

//utils.c
void		free_str_array(char **str_array);
//solo para pruebas
void	print_split(char **line_splited);

//parse.c
int			check_closed_quotes(char *line, int q, int i, char in_quot);
int			check_quotes(char *line, int q, int i);
char		set_in_quot(char *line, int i);

//lexer.c
char		**create_line_splited(char *line);

#endif