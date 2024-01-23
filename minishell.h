/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:14:24 by nmontiel          #+#    #+#             */
/*   Updated: 2024/01/19 16:36:33 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
//void		ft_leaks(void);

//utils.c
void		free_str_array(char **str_array);

#endif