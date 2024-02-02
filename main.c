
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

void	initialize_minishell(t_data **shell, char **env)
{
	(void)env;
	*shell = (t_data *)malloc(sizeof(t_data));
	if (!*shell)
	{
		perror("Error al asignar memoria para t_data");
		exit(EXIT_FAILURE);
	}
	//initialize_env(*shell, env);
}

void	process_builtins(t_data *shell)
{
	if (ft_strncmp(shell->line, "exit\0", 5) == 0
		|| ft_strncmp(shell->line, "EXIT\0", 5) == 0)
	{
		free(shell->line);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(shell->line, "env\0", 4) == 0
		|| ft_strncmp(shell->line, "ENV\0", 4) == 0)
		env_command(shell);
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
	//int			len;
	char		*line;

	words_splited = (t_list **)malloc(sizeof(t_list *));
	if (!words_splited)
		printf("error: malloc\n"); //Hacer función para enviar errores a stderr
	while (1)
	{
		shell->line = readline("Minishell@ ~ ");
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
				shell->line = readline("Minishell@ ~ ");
			}
			if (shell->line && *shell->line)
			{
				line = ft_strdup(shell->line);
				printf("line = %s\n", line);
				words_splited = create_line_splited(line, words_splited);
				print_list_splited(words_splited);
				shell->echo = ft_split(shell->line, ' ');
				if (shell->echo && shell->echo[0] != NULL)
				{
					if (*shell->line)
						add_history(shell->line);
					process_builtins(shell);
					free_echo(shell->echo);
					free(shell->line);
				}
				else
					free(shell->line);
			}
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argv;
	atexit(ft_leaks);
	initialize_minishell(&shell, env);
	shell->line = NULL;
	if (argc == 1)
	{
		ft_header();
		start_minishell(shell);
	}
	free(shell);
	clear_history();
	return (EXIT_SUCCESS);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}


/*
void	run_shell(char **env)
{
	t_prompt	prompt;	
	char		*line;
	char		cwd[500];
	int			q;
	//int			words_count;
	//char		**first_split;
	t_list		**words_splited;

	prompt.envp = env;
	words_splited = (t_list **)malloc(sizeof(t_list *));
	if (!words_splited)
		printf("error: malloc\n"); //Hacer función para enviar errores a stderr
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf(MAGENTA "Minishell@" YELLOW "%s ~\n" RESET, cwd);
		else
			perror("getcwd() error");
		line = readline(BLUE "Minishell@ ~ " RESET);
		if (line && *line)
			add_history(line);
		if (line == NULL)
			break ;
		q = check_quotes(line, 0, 0);
		//printf("q = %d\n", q);
		if (q % 2 != 0)
			printf("error: dequoted line\n"); //Hacer función para enviar errores a stderr
		//words_count = word_counter(line);
		words_splited = create_line_splited(line, words_splited);
		//printf("words: %d\n", words_count);
		words_splited = split_pipes(words_splited);
		print_list_splited(words_splited);
		process_line(line, &prompt.envp);
		free(line);
	}
}

void	process_line(char *line, char ***env)
{
	char		**args;

	args = ft_split(line, ' ');
	if (args[0] != NULL)
	{
		if (ft_strncmp(args[0], "exit\0", 5) == 0)
		{
			free(line);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(args[0], "env\0", 4) == 0)
			env_command(*env);
		if (ft_strncmp(args[0], "pwd\0", 4) == 0)
			pwd_command();
		if (args[0] != NULL && ft_strncmp(args[0], "echo\0", 5) == 0)
			echo_command(args);
	}
	free_str_array(args);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	atexit(ft_leaks);
	if (argc == 1)
	{
		ft_header();
		run_shell(env);
	}
	//rl_clear_history();
	return (EXIT_SUCCESS);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}
*/