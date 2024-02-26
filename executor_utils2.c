#include "minishell.h"

static char	*prepare_local_command(t_process *process)
{
	char	*full_path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error getting current working directory");
		return (NULL);
	}
	full_path = malloc(sizeof(char) * (ft_strlen(cwd) + 1
				+ ft_strlen(process->command) + 1));
	if (!full_path)
	{
		perror("Error allocating memory for full path");
		free(cwd);
		return (NULL);
	}
	ft_strlcpy(full_path, cwd, sizeof(full_path));
	ft_strlcat(full_path, "/", sizeof(full_path));
	ft_strlcat(full_path, process->command, sizeof(full_path));
	free(cwd);
	return (full_path);
}

static int	execute_prepared_command(t_process *process, char *full_path)
{
	if (access(full_path, F_OK | X_OK) == -1)
	{
		printf("Error: command '%s' not found or not executable\n",
			process->command);
		return (-1);
	}
	process->pid = fork();
	if (process->pid == -1)
	{
		perror("Error creating child process");
		return (-1);
	}
	if (process->pid == 0)
	{
		execve(full_path, process->args, process->env);
		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
	waitpid(process->pid, &process->status, 0);
	return (0);
}

int	execute_local_command(t_process *process)
{
	int		result;
	char	*full_path;

	full_path = prepare_local_command(process);
	if (!full_path)
		return (-1);
	result = execute_prepared_command(process, full_path);
	free(full_path);
	return (result);
}
