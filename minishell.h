
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

typedef struct s_mini
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	char	**envp;
	pid_t	pid;
	int		g_status;
}				t_prompt;

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
//void		ft_leaks(void);

//utils.c
void		free_str_array(char **str_array);

#endif