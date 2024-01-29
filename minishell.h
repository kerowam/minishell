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

# define RESET			"\x1B[0m"
# define BOLD_MAGENTA	"\x1B[1;35m"
# define LIGHT_CYAN		"\x1B[96m"
# define BOLD_WHITE		"\x1B[1;37m"
# define BOLD_BLUE		"\x1B[1;34m"

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
	t_env	*env;
	t_env	*temp_env;
}				t_data;

//builtins.c
void	env_command(t_data *shell);
void	pwd_command(t_data *shell);
void	echo_command(char **str, int exists);
void	unset_command(t_data *shell, char *name);

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

//main.c
void	initialize_minishell(t_data **shell, char **env);
void	process_builtins(t_data *shell);
void	start_minishell(t_data *shell);
void	ft_header(void);
int		main(int argc, char **argv, char **env);
//void	ft_leaks(void);

//utils.c
void	free_temp(char **temp);
void	free_echo(char **str);

#endif
