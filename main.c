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
	*shell = (t_data *)malloc(sizeof(t_data));
	if (!*shell)
	{
		perror("Error al asignar memoria para t_data");
		exit(EXIT_FAILURE);
	}
	printf("Ha alojado memoria para shell\n");
	initialize_env(*shell, env);
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
		env_command(shell->echo, shell);
	if (ft_strncmp(shell->line, "pwd\0", 4) == 0
		|| ft_strncmp(shell->line, "PWD\0", 4) == 0)
		pwd_command(shell);
	if (ft_strncmp(shell->echo[0], "echo\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "ECHO\0", 5) == 0)
		echo_command(shell->echo, 0);
	if (ft_strncmp(shell->echo[0], "unset\0", 6) == 0
		|| ft_strncmp(shell->echo[0], "UNSET\0", 6) == 0)
		unset_command(shell, shell->echo[1]);
	if (ft_strncmp(*shell->echo, "cd\0", 3) == 0
		|| ft_strncmp(*shell->echo, "CD\0", 3) == 0)
		cd_command(shell->echo, shell);
	if (ft_strncmp(shell->echo[0], "export\0", 7) == 0
		|| ft_strncmp(shell->echo[0], "EXPORT\0", 7) == 0)
		export_command(shell->echo, shell);
}

void	start_minishell(t_data *shell)
{
	while (1)
	{
		shell->line = readline("Minishell@ ~ ");
		if (shell->line != NULL && *shell->line != '\0')
		{
			shell->echo = ft_split(shell->line, ' ');
			if (shell->echo && shell->echo[0] != NULL)
			{
				add_history(shell->line);
				process_builtins(shell);
				free_echo(shell->echo);
			}
			free(shell->line);
		}
		else if (shell->line != NULL)
			free(shell->line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	printf("Inicio del programa\n");
	(void)argv;
	atexit(ft_leaks);
	printf("PRUEBA\n");
	initialize_minishell(&shell, env);
	printf("PRUEBA 1");
	shell->line = NULL;
	if (argc == 1)
	{
		ft_header();
		start_minishell(shell);
	}
	free(shell);
	clear_history();
	printf("Fin del programa\n");
	return (EXIT_SUCCESS);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

/*void	start_minishell(t_data *shell)
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
			printf("Ha entrado en else\n");
			q = check_quotes(shell->line, 0, 0);
			printf("Ha chequeado las quotes\n");
			if (q % 2 != 0)
			{
				printf("error: dequoted line\n");
				free(shell->line);
				//start_minishell(shell); //Hay que buscar otra solución
				shell->line = readline("Minishell@ ~ ");
			}
			printf("Ha salido de la comprobacion de q\n");
			if (shell->line && *shell->line)
			{
				printf("Ha entrado en shell->line\n");
				line = ft_strdup(shell->line);
				printf("Ha añadido shell->line a line\n");
				//printf("line = %s\n", line);
				words_splited = create_line_splited(line, words_splited);
				printf("Ha creado la linea spliteada\n");
				free(line);
				words_splited = split_pipes(words_splited);
				words_splited = split_redirections(words_splited);
				words_splited = expander(shell->env, words_splited);
				//words_splited = test_quot_cleaner(words_splited);
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
}*/
