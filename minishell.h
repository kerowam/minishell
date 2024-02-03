
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

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	char	**envp;
	char	*cd;
	char	*cd1;
	char	**echo;
	char	*line;	
	char	cwd[500];
	int		del; //delimitador para variables
	int		f_pipe;
	t_env	*env;
	t_env	*temp_env;
	t_env	*export;
	t_env	*temp_export;
}				t_data;

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
void	env_command(t_data *shell);
void	pwd_command(t_data *shell);
void	echo_command(char **str, int exists);
void	unset_command(t_data *shell, char *name);
void	export_command(char **cmd, t_data *shell);

//cd_utils.c
void	update_pwd(t_data *shell);
void	update_oldpwd(t_data *shell);
void	update_oldpwd_again(t_data *shell, char *pwd);
void	obtain_env(t_data *shell, char *env_var);

//cd.c
void	handle_home_directory(t_data *shell);
void	handle_previous_directory(t_data *shell);
void	handle_given_directory(char **str, t_data *shell);
void	cd_command(char **str, t_data *shell);
int		handle_directory(t_data *shell, char **str);

//enviroment.c
void	initialize_env(t_data *shell, char **env);
void	add_newenv_back(t_env **first, t_env *new, char **temp);
void	add_oldpwd(t_data *shell);
char	*ft_get_env_name(char *fullenv);
char	*ft_get_env_value(char *fullenv);

//export_utils.c
void	ft_non_arg_export(t_data *shell);
void	save_variable(char *variable, t_data *shell);
bool	input_checker(char *arg, char *cmd);
int		check_variable(char *name, char *value, t_data *shell);
t_env	*ft_new_env_node(char *name, char *value);

//export_utils.c
void	ft_non_arg_export(t_data *shell);
void	save_variable(char *variable, t_data *shell);
bool	input_checker(char *arg, char *cmd);
int		check_variable(char *name, char *value, t_data *shell);
t_env	*ft_new_env_node(char *name, char *value);

//main.c
void	initialize_minishell(t_data **shell, char **env);
void	process_builtins(t_data *shell);
void	start_minishell(t_data *shell);
void	ft_header(void);
int		main(int argc, char **argv, char **env);
void	ft_leaks(void);

//utils.c
void	free_temp(char **temp);
void	free_echo(char **str);
void	env_add_back(t_env **root, t_env *new);
//solo para pruebas
void	print_split(char **line_splited);
void	print_list_splited(t_list **list);

//parse.c
int		check_closed_quotes(char *line, int q, int i, char in_quot);
int		check_quotes(char *line, int q, int i);
char	set_in_quot(char *line, int i);

//lexer.c
t_list	**create_line_splited(char *line, t_list **list);

//lexer_pipes.c
t_list	**split_pipes(t_list **list);
t_list	*split_pipe(t_list *list, int i);
t_list	**handle_pipes(t_list **list, int i);

//lexer_utils.c
void	insert_node(t_list **list, char *content);
int		get_end_index(char *line, int i);
char	*get_tmp_split(int target_index, char *tmp_word, int i);
t_list	**handle_quotes(t_list **list);

// lexer_pipes_utils.c
int		get_pipe_nbr(char *line, int i);
int		get_pipe_index(char *line, int i);

//lexer_redir.c
t_list	**split_redirections(t_list **list);

//lexer_redir_utils.c
int		get_redir_index(char *line, int i);
int		insert_redirs(char redir, t_list *list, char *tmp_word, int i);
void	set_redir(t_list *list, char redir, char *tmp_word, int i);
int		get_redirection_nbr(char *line, int i);

#endif