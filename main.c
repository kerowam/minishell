
#include "minishell.h"
/*void	ft_header(void)
{
	printf("\n");
	printf("               ╔╗ ╔╦═══╗ \n");
	printf("               ║║ ║║╔═╗║ \n");
	printf("               ║╚═╝╠╝╔╝║ \n");
	printf("               ╚══╗╠═╝╔╝ \n");
	printf("                  ║║║╚═╗ \n");
	printf("                  ╚╩═══╝ \n");
	printf("   ╔═╗╔═╦══╦═╗ ╔╦══╦═══╦╗ ╔╦═══╦╗  ╔╗    \n");
	printf("   ║║╚╝║╠╣╠╣║╚╗║╠╣╠╣╔═╗║║ ║║╔══╣║  ║║    \n");
	printf("   ║╔╗╔╗║║║║╔╗╚╝║║║║╚══╣╚═╝║╚══╣║  ║║    \n");
	printf("   ║║║║║║║║║║╚╗║║║║╚══╗║╔═╗║╔══╣║ ╔╣║ ╔╗ \n");
	printf("   ║║║║║╠╣╠╣║ ║║╠╣╠╣╚═╝║║ ║║╚══╣╚═╝║╚═╝║ \n");
	printf("   ╚╝╚╝╚╩══╩╝ ╚═╩══╩═══╩╝ ╚╩═══╩═══╩═══╝ \n");
	printf("\n");
}*/

int	g_status;

void	initialize_minishell(t_data **shell, char **env)
{
	(void)env;
	g_status = 0;
	*shell = (t_data *)malloc(sizeof(t_data));
	if (!*shell)
	{
		put_error(MEMPROBLEM, 1);
		exit(g_status);
	}
}

void	start_minishell(t_data *shell, char **env)
{
	int			q;
	t_list		**redir_splited;
	t_process	*process;
	int			i;

	(void)env;
	while (1)
	{
		setup_signal_handlers();
		system("leaks -q minishell");
		if (shell->line)
			free(shell->line);
		shell->line = readline("Minishell@ ~ ");
		if (shell->line == NULL)
			exit(g_status);
		//printf("shell->line: %s\n", shell->line);
		i = 0;
		while (shell->line[i] == ' ')
			i++;
		if (shell->line[i] == '\0')
		{
			free(shell->line);
			shell->line = NULL;
		}
		if (shell->line && *shell->line)
		{
			redir_splited = (t_list **)malloc(sizeof(t_list *));
			if (!redir_splited)
			{
				put_error(MEMPROBLEM, 1);
				return ;
			}
			process = (t_process *)malloc(sizeof(t_process));
			if (!process)
			{
				put_error(MEMPROBLEM, 1);
				return ;
			}
		}
		//printf("24.1.start minishell shell->line pointer = %p\n", shell->line);
		//printf("24.2.start minishell readline = %p\n", readline);
		if (shell->line == NULL)
			printf("\n");
		else
		{
			q = check_quotes(shell->line, 0, 0);
			if (q % 2 != 0)
			{
				put_error(DEQUOTE, 1);
				free (redir_splited);
				free (process);
				//free(shell->line);
				//rl_replace_line("", 0);
			}
			else if (shell->line && *shell->line)
			{
				lexer(shell, redir_splited);
				//print_list_splited(redir_splited);
				parse(process, redir_splited);
				ft_free_list(redir_splited);
				//print_process(process);
				shell->echo = ft_split(shell->line, ' ');
				if (shell->echo && shell->echo[0] != NULL)
				{
					if (*shell->line)
						add_history(shell->line);
					if (is_builtin(process, shell))
						execute_builtin(process, shell);
					if (!is_builtin(process, shell))
						main_executor(shell, process);
					free(shell->line);
					free_echo(shell->echo);
					shell->line = NULL;
					//free(shell);
					if (process != NULL)
						free_process(process);
				}
				else
				{
					free(shell->line);
					shell->line = NULL;
				}
			}
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data		*shell;

	(void)argv;
	if (argc == 1)
	{
		atexit(ft_leaks);
		shell = NULL;
		initialize_minishell(&shell, env);
		copy_env_to_data(shell, env);
		shell->line = NULL;
		if (argc == 1)
		{
			//ft_header();
			start_minishell(shell, env);
		}
		free(shell->line);
		free(shell->echo);
		free(shell);
		clear_history();
		return (g_status);
	}
	put_error(ARGS, 1);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}
