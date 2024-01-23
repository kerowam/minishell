
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

void	run_shell(char **env)
{
	t_prompt	prompt;	
	char		*line;
	char		cwd[500];

	prompt.envp = env;
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf(MAGENTA "Minishell@" YELLOW "%s ~ " RESET, cwd);
		else
			perror("getcwd() error");
		line = readline("");
		add_history(line);
		if (line == NULL)
			break ;
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
		if (ft_strncmp(args[0], "cd\0", 3) == 0)
			cd_command(args[1]);
		if (args[0] != NULL && ft_strncmp(args[0], "echo\0", 5) == 0)
			echo_command(args);
		if (args[0] != NULL && ft_strncmp(args[0], "unset\0", 6) == 0)
			unset_command(args, env);
		if (args[0] != NULL && ft_strncmp(args[0], "export\0", 7) == 0)
			export_func(env, args[1]);
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
	clear_history();
	return (EXIT_SUCCESS);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}
