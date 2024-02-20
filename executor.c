#include "minishell.h"

int	check_command_access(t_process *process)
{
	int		i;
	char	*full_path;
	char	*temp;
	char	**cmd_argv;
	t_list	*current;
	int		j;
	int		k;

	i = 0;
	while (process->env[++i] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		printf("Temp: %s\n", temp);
		full_path = ft_strjoin(temp, process->command);
		printf("Full Path: %s\n", full_path);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			printf("ACCESO\n");
			printf("%s\n", process->command);
			cmd_argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
			if (!cmd_argv)
			{
				perror("Error al asignar memoria para cmd_argv");
				exit(EXIT_FAILURE);
			}
			cmd_argv[0] = ft_strdup(process->command);
			current = process->argv;
			j = 1;
			while (current)
			{
				cmd_argv[j] = ft_strdup(current->content);
				current = current->next;
				j++;
			}
			cmd_argv[j] = NULL;
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
			free(temp);
			free(full_path);
			k = 0;
			while (k <= j)
			{
				free(cmd_argv[k]);
				k++;
			}
			free(cmd_argv);
			return (1);
		}
		else
		{
			printf("NO ACCESO\n");
			free(full_path);
		}
		free(temp);
	}
	return (0);
}

void	execute_local_command(t_process *process)
{
	char	full_path[1000];
	char	*cwd;
	char	**cmd_argv;
	t_list	*current;
	int		j;

	cwd = getcwd(NULL, 0);
	ft_strlcpy(full_path, cwd, sizeof(full_path));
	ft_strlcat(full_path, "/", sizeof(full_path));
	ft_strlcat(full_path, process->command, sizeof(full_path));
	if (access(full_path, F_OK | X_OK) != -1)
	{
		printf("ACCESO\n");
		printf("Command path: %s\n", full_path);
		cmd_argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
		if (!cmd_argv)
		{
			perror("Error al asignar memoria para cmd_argv");
			free(cwd);
			exit(EXIT_FAILURE);
		}
		cmd_argv[0] = ft_strdup(process->command);
		current = process->argv;
		j = 1;
		while (current)
		{
			cmd_argv[j] = ft_strdup(current->content);
			current = current->next;
			j++;
		}
		cmd_argv[j] = NULL;
		process->pid = fork();
		if (process->pid == -1)
		{
			perror("Error al crear el proceso hijo");
			free(cwd);
			exit(EXIT_FAILURE);
		}
		else if (process->pid == 0)
		{
			execve(full_path, cmd_argv, process->env);
			perror("Error al ejecutar el comando\n");
			exit(EXIT_FAILURE);
		}
		waitpid(process->pid, &process->status, 0);
		free(cmd_argv);
		free(cwd);
		return ;
	}
	else
		printf("NO ACCESO\n");
	free(cwd);
}

int	main_executor(t_data *shell, char **env, t_process *process)
{
	if (!process)
		exit(EXIT_FAILURE);
	if (is_builtin(process, shell))
		execute_builtin(process, shell);
	else if (!is_builtin(process, shell))
	{
		find_path(process, env);
		printf("%s\n", process->command);
		check_command_access(process);
		if (ft_strncmp(process->command, "clear", 5) == 0)
			printf("\033[H\033[J");
		if (starts_with_dot_slash(process->command))
			execute_local_command(process);
		return (EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}