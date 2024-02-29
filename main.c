
#include "minishell.h"

void	ft_header(void)
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
}
/*
void	initialize_minishell(t_data **shell, char **env)
{
	(void)env;
	*shell = (t_data *)malloc(sizeof(t_data));
	if (!*shell)
	{
		put_error(MEMPROBLEM, 1); //exit status 1???
		exit(EXIT_FAILURE); //Debe terminar el programa, o comenzar de nuevo?
	}
	initialize_env(*shell, env);
}

void	process_builtins(t_data *shell)
{
	if (ft_strncmp(shell->line, "exit\0", 5) == 0
		|| ft_strncmp(shell->line, "EXIT\0", 5) == 0)
	{
		free(shell->line);
		//Liberar variables
		exit (g_exit_status); //He cambiado el exit status
	}
	if (ft_strncmp(shell->line, "env\0", 4) == 0
		|| ft_strncmp(shell->line, "ENV\0", 4) == 0)
		env_command(shell->echo, shell);
	if (ft_strncmp(shell->line, "pwd\0", 4) == 0
		|| ft_strncmp(shell->line, "PWD\0", 4) == 0)
		pwd_command(shell);
	if (ft_strncmp(shell->echo[0], "echo\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "ECHO\0", 5) == 0)
		echo_command(shell->echo, 0);
	if (ft_strncmp(shell->line, "unset\0", 6) == 0
		|| ft_strncmp(shell->line, "UNSET\0", 6) == 0)
		unset_command(shell, shell->echo[1]);
	if (ft_strncmp(*shell->echo, "cd\0", 3) == 0
		|| ft_strncmp(shell->line, "CD\0", 3) == 0)
		cd_command(shell->echo, shell);
	if (ft_strncmp(shell->echo[0], "export\0", 7) == 0
		|| ft_strncmp(shell->echo[0], "EXPORT\0", 7) == 0)
		export_command(shell->echo, shell);
}

void	start_minishell(t_data *shell)
{
	int			q;
	t_list		**words_splited;
	t_process	*process;

	words_splited = (t_list **)malloc(sizeof(t_list *));
	process = (t_process *)malloc(sizeof(t_process));
	if (!words_splited)
		put_error(MEMPROBLEM, 1);
	while (1)
	{*/
		/*if (words_splited)
			free(words_splited);*/
		/*if (shell->line)
		{
			free(shell->line);
			shell->line = NULL;
		}*/
		/*shell->line = readline("Minishell@ ~ ");
		if (shell->line == NULL)
			printf("\n");
		else
		{
			q = check_quotes(shell->line, 0, 0);
			if (q % 2 != 0)
			{
				put_error(DEQUOTE, 1);
				free(shell->line);
				//start_minishell(shell); //Hay que buscar otra solución
				//rl_replace_line("Minishell@ ~ ", 1);
				//break ;
				shell->line = readline("Minishell@ ~ ");
			}
			if (shell->line && *shell->line)
			{
				lexer(shell, words_splited);
				//print_list_splited(words_splited);
				parse(process, words_splited);
				free_list(words_splited);
				//print_process(process);
				shell->echo = ft_split(shell->line, ' ');
				if (shell->echo && shell->echo[0] != NULL)
				{
					if (*shell->line)
						add_history(shell->line);
					process_builtins(shell);
					free_echo(shell->echo);
					free(shell->line);
					//exit (g_exit_status);
					break ;
				}
				else
					free(shell->line);
			}
		}
	}
}*/

void	initialize_minishell(t_data **shell, char **env)
{
	(void)env;
	*shell = (t_data *)malloc(sizeof(t_data));
	if (!*shell)
	{
		perror("Error al asignar memoria para t_data");
		exit(EXIT_FAILURE);
	}
}

void	start_minishell(t_data *shell, char **env)
{
	int			q;
	t_list		**words_splited;
	t_process	*process;

	(void)env;
	while (1)
	{
		words_splited = (t_list **)malloc(sizeof(t_list *));
		printf("23.start minishell words_splited pointer = %p\n", words_splited);
		if (!words_splited)
			printf("error: malloc\n"); //Hacer función para enviar errores a stderr
			//gestionar error.
		//words_splited = NULL;
		process = (t_process *)malloc(sizeof(t_process));
		if (!process)
		{
			printf("error: malloc\n");
			//gestionar error.
		}
		printf("24.start minishell process pointer = %p\n", process);
		
		/*if (words_splited)
			free(words_splited);*/
		/*if (shell->line)
		{
			free(shell->line);
			//shell->line = NULL;
		}*/
		shell->line = readline("Minishell@ ~ ");
		printf("24.1.start minishell shell->line pointer = %p\n", shell->line);
		printf("24.2.start minishell readline = %p\n", readline);
		if (shell->line == NULL)
			printf("\n");
		else
		{
			q = check_quotes(shell->line, 0, 0);
			if (q % 2 != 0)
			{
				printf("error: dequoted line\n");
				free(shell->line);
				//start_minishell(shell); //Hay que buscar otra solución
				//rl_replace_line("Minishell@ ~ ", 1);
				shell->line = readline("Minishell@ ~ ");
			}
			if (shell->line && *shell->line)
			{
				words_splited = lexer(shell, words_splited);
				print_list_splited(words_splited);
				parse(process, words_splited);
				print_process(process);
				free_list(words_splited);
				if (words_splited != NULL)
					free(words_splited);
				shell->echo = ft_split(shell->line, ' ');
				if (shell->echo && shell->echo[0] != NULL)
				{
					if (*shell->line)
						add_history(shell->line);
					if (is_builtin(process, shell))
						execute_builtin(process, shell);
					if (!is_builtin(process, shell))
						main_executor(shell, process);
					free_echo(shell->echo);
					free(shell->line);
					if (process != NULL)
					{
						free_process(process);
						//free(process);
					}
					//free(words_splited);
					//exit (g_exit_status);
					//break ;
				}
				else
					free(shell->line);
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
			ft_header();
			start_minishell(shell, env);
		}
		free(shell->line);
		free(shell->echo);
		free(shell);
		clear_history();
		return (EXIT_SUCCESS);
	}
	printf("Error de argumentos\n");
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}
