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
	//printf("Variables de entorno después de initialize_env:\n");
	//print_env_list((*shell)->env);
}

void	start_minishell(t_data *shell)
{
	while (1)
	{
		shell->line = readline("Minishell@ ~ ");
		//printf("Comando introducido: %s\n", shell->line);
		if (shell && *(shell->line))
			add_history(shell->line);
		if (shell->line == NULL)
			break ;
		if (ft_strncmp(shell->line, "exit\0", 5) == 0)
		{
			free(shell->line);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(shell->line, "env\0", 4) == 0)
			env_command(shell);
		if (ft_strncmp(shell->line, "pwd\0", 4) == 0)
			pwd_command(shell);
		free(shell->line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argv;
	//atexit(ft_leaks);
	initialize_minishell(&shell, env);
	if (argc == 1)
	{
		ft_header();
		start_minishell(shell);
	}
	free(shell);
	clear_history();
	return (EXIT_SUCCESS);
}

/*void	print_env_list(t_env *env)
{
	while (env != NULL)
	{
		printf("%s%s\n", env->name, env->value);
		env = env->next;
	}
}*/

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}*/
