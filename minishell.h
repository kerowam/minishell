
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

int		g_exit_status;

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
	char	**temp;
	t_env	*temp_env;
	t_env	*export;
	t_env	*temp_export;
}				t_data;

typedef struct s_process
{
	struct s_process	*next_process;
	char				*command;
	//t_list				*flags;
	t_list				*argv;
	char				**args;
	pid_t				pid;//
	char				*infile;
	int					inf;//
	char				*outfile;
	int					outf;//
	char				*outfile_append;
	t_list				*here_doc;
	int					stderr;//??
	int					completed;//????
	int					stopped;//????
	int					status;
	char				**env;
	char				*path_env;
}				t_process;

enum	e_error
{
	DEQUOTE = 1, //g_exit_status = 1?
	NOTFILEORDIR = 2, //g_exit_status = 1
	NOTPERMISSION = 3, //g_exit_status = 1
	NOTCOMMAND = 4, //g_exit_status = 127
	DUPERROR = 5, //g_exit_status = 1 Por si falla dup2??
	FORKERROR = 6, //g_exit_status = 1 Por si falla fork
	PIPEERROR = 7, //g_exit_status = 1 Por si falla pipe
	UNEXPECTEDTOKEN = 8, //g_exit_status = 258
	MEMPROBLEM = 9, //g_exit_status = ? Por si falla malloc
	ISDIR = 10, //g_exit_status = 126
	NOTDIR = 11, //g_exit_status = 1
	OPENERROR = 12 //g_exit_status = 1? Por si falla open (fd < 0)
};

//builtins.c
void	env_command(char **cmd, t_data *shell);
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
void	add_path(t_data *shell);
void	add_oldpwd(t_data *shell);

//export_utils.c
void	only_export(t_data *shell);
void	create_variable(char *variable, t_data *shell);
bool	check_args(char *arg, char *cmd);
int		check_if_exists(char *name, char *value, t_data *shell);
t_env	*new_node(char *name, char *value);

//main.c
void	initialize_minishell(t_data **shell, char **env);
void	start_minishell(t_data *shell, char **env);
void	ft_header(void);
int		main(int argc, char **argv, char **env);
void	ft_leaks(void);

//utils.c
void	env_add_back(t_env **root, t_env *new);

//solo para pruebas
void	print_split(char **line_splited);
void	print_list_splited(t_list **list);
void	print_process(t_process *process);

//quotes.c
int		check_closed_quotes(char *line, int q, int i, char in_quot);
int		check_quotes(char *line, int q, int i);
char	set_in_quot(char *line, int i);

//lexer.c
void	create_line_splited(char *line, t_list **list);
void	lexer(t_data *shell, t_list **words_splited);

//lexer_pipes.c
void	split_pipes(t_list **list);
void	split_pipe(t_list *list, int i);
void	handle_pipes(t_list **list, int i);

//lexer_utils.c
void	insert_node(t_list **list, char *content);
int		get_end_index(char *line, int i);
char	*get_tmp_split(int target_index, char *tmp_word, int i);
int		search_end_quoted_string(char q, char *line, int i);

// lexer_pipes_utils.c
int		get_pipe_nbr(char *line, int i);
int		get_pipe_index(char *line, int i);

//lexer_redir.c
void	split_redirections(t_list **list);

//lexer_redir_utils.c
int		get_redir_index(char *line, int i);
int		insert_redirs(char redir, t_list *list, char *tmp_word, int i);
void	set_redir(t_list *list, char redir, char *tmp_word, int i);
int		get_redirection_nbr(char *line, int i);

//expander.c
void	expander(t_env *env, t_list **line_splited);

//expander_utils.c
int		get_len_word(char *str, int i);
char	*set_key(char *str, int i);

//quote_cleaner.c
void	quot_cleaner(t_list **list);
char	*add_quot_substr(int start, int i, char *str, char *end_str);
char	*add_substr(int start, int i, char *str, char *end_str);
void	clean_str_quot(char *str, t_list **list);

//parser.c
void	parse(t_process *process, t_list **words_splited);

//executor.c
int		find_path(t_process *process, char **env);
int		main_executor(t_data *shell, char **env, t_process *process);
void	execute_builtin(t_process *process, t_data *shell);
bool	is_builtin(t_process *process, t_data *shell);
void	free_string_array(char **array);

//utils2.c
void	print_list_splited(t_list **list);
void	print_process(t_process *process);
char	*obtain_env_name(char *fullenv);
char	*obtain_env_value(char *fullenv);

//error.c
void	put_error(int error_tipe, int error_code);

//free.c
void	free_temp(char **temp);
void	free_echo(char **str);
void	free_list(t_list **list);
void	free_env_list(t_env *env);
void	free_process(t_process *process);

#endif