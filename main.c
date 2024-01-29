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
	else if (ft_strncmp(shell->line, "env\0", 4) == 0
		|| ft_strncmp(shell->line, "ENV\0", 4) == 0)
		env_command(shell);
	else if (ft_strncmp(shell->line, "pwd\0", 4) == 0
		|| ft_strncmp(shell->line, "PWD\0", 4) == 0)
		pwd_command(shell);
	else if (ft_strncmp(shell->echo[0], "echo\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "ECHO\0", 5) == 0)
		echo_command(shell->echo, 0);
	else if (ft_strncmp(shell->line, "unset\0", 6) == 0
		|| ft_strncmp(shell->line, "UNSET\0", 6) == 0)
		unset_command(shell, shell->echo[1]);
	else if (ft_strncmp(*shell->echo, "cd\0", 3) == 0
		|| ft_strncmp(shell->line, "CD\0", 3) == 0)
		cd_command(shell->echo, shell);
	else
		printf("zsh: command not found: %s\n", shell->line);
}

void	start_minishell(t_data *shell)
{
	while (1)
	{
		shell->line = readline("Minishell@ ~ ");
		shell->echo = ft_split(shell->line, ' ');
		if (!shell->echo)
			exit(EXIT_SUCCESS);
		if (shell && *(shell->line))
			add_history(shell->line);
		if (shell->line == NULL)
			break ;
		process_builtins(shell);
		free_echo(shell->echo);
		free(shell->line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argv;
	//atexit(ft_leaks);
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

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}*/