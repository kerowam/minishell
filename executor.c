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
	int		original_stdout;

	i = 0;
	original_stdout = dup(STDOUT_FILENO);
	cmd_argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
	if (!cmd_argv)
	{
		perror("Error allocating memory for cmd_argv");
		exit(EXIT_FAILURE);
	}
	while (process->env[++i] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		full_path = ft_strjoin(temp, process->command);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			redirect_outfile_append(process);
			redirect_outfile(process);
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
				redirect_infile(process);
				execve(full_path, cmd_argv, process->env);
				perror("Error al ejecutar el comando\n");
				exit(EXIT_FAILURE);
			}
			waitpid(process->pid, &process->status, 0);
			if (ft_strcmp(process->command, "cat") == 0)
				printf("\n");
			dup2(original_stdout, STDOUT_FILENO);
			close(original_stdout);
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
			free(full_path);
		free(temp);
	}
	free(cmd_argv);
	return (0);
}

int	main_executor(t_data *shell, t_process *process)
{
	if (!process)
		exit(EXIT_FAILURE);
	if (is_builtin(process, shell))
		execute_builtin(process, shell);
	else if (!is_builtin(process, shell))
	{
		if (!process->command)
		{
			if (!process->here_doc)
				return (EXIT_FAILURE);
			else
				handle_heredoc(process);
		}
		find_path(process, shell);
		if (!check_command_access(process) && process->command
			&& !(starts_with_dot_slash(process->command)))
		{
			printf("zsh: command not found: %s\n", process->command);
			return (EXIT_FAILURE);
		}
		if (process->command)
		{
			if (ft_strncmp(process->command, "clear", 5) == 0)
				printf("\033[H\033[J");
		}
		if (starts_with_dot_slash(process->command))
			execute_local_command(process);
		return (EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
