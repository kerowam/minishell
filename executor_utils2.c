#include "minishell.h"

static void	prepare_command_arguments(t_process *process, char ***cmd_argv)
{
	t_list	*current;
	int		j;

	*cmd_argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
	if (!*cmd_argv)
	{
		perror("Error al asignar memoria para cmd_argv");
		exit(EXIT_FAILURE);
	}
	(*cmd_argv)[0] = ft_strdup(process->command);
	//printf("2. prepare_command_arguments cmd_argv pointer = %p\n", *cmd_argv);
	current = process->argv;
	j = 1;
	while (current)
	{
		(*cmd_argv)[j] = ft_strdup(current->content);
		//printf("3. prepare_command_arguments cmd_argv[%d] pointer = %p\n", j, (*cmd_argv)[j]);
		current = current->next;
		j++;
	}
	(*cmd_argv)[j] = NULL;
}

static void	execute_child_process(t_process *process,
		char *full_path, char **cmd_argv)
{
	process->pid = fork();
	if (process->pid == -1)
	{
		perror("Error al crear el proceso hijo");
		exit(EXIT_FAILURE);
	}
	else if (process->pid == 0)
	{
		execve(full_path, cmd_argv, process->env);
		perror("Error al ejecutar el comando\n");
		exit(EXIT_FAILURE);
	}
	waitpid(process->pid, &process->status, 0);
	free_argv(cmd_argv);
}

void	execute_local_command(t_process *process)
{
	char	full_path[1000];
	char	*cwd;
	char	**cmd_argv;

	cwd = getcwd(NULL, 0);
	ft_strlcpy(full_path, cwd, sizeof(full_path));
	ft_strlcat(full_path, "/", sizeof(full_path));
	ft_strlcat(full_path, process->command, sizeof(full_path));
	if (access(full_path, F_OK | X_OK) != -1)
	{
		prepare_command_arguments(process, &cmd_argv);
		execute_child_process(process, full_path, cmd_argv);
		return ;
	}
	free(cwd);
}
