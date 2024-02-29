#include "minishell.h"

static void	execute_command(t_process *process, char *full_path,
		char **cmd_argv)
{
	process->pid = fork();
	if (process->pid == -1)
	{
		perror("Error creating child process");
		exit(EXIT_FAILURE);
	}
	else if (process->pid == 0)
	{
		redirect_infile(process);
		execve(full_path, cmd_argv, process->env);
		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
	waitpid(process->pid, &process->status, 0);
}

static void	setup_command_and_redirects(t_process *process, char **cmd_argv,
		int *j)
{
	t_list	*current;

	redirect_outfile_append(process);
	redirect_outfile(process);
	cmd_argv[0] = ft_strdup(process->command);
	current = process->argv;
	*j = 1;
	while (current)
	{
		cmd_argv[*j] = ft_strdup(current->content);
		current = current->next;
		(*j)++;
	}
	cmd_argv[*j] = NULL;
}

static void	execute_single_command(t_process *process, char *full_path,
	char **cmd_argv, int original_stdout)
{
	int	j;
	int	k;

	setup_command_and_redirects(process, cmd_argv, &j);
	execute_command(process, full_path, cmd_argv);
	if (ft_strcmp(process->command, "cat") == 0)
		printf("\n");
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	free(full_path);
	k = 0;
	while (cmd_argv[k] != NULL)
	{
		free(cmd_argv[k]);
		k++;
	}
	free(cmd_argv);
}

int	check_command_access(t_process *process)
{
	int		i;
	char	*full_path;
	char	*temp;
	char	**cmd_argv;
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
	while (process->env[i] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		full_path = ft_strjoin(temp, process->command);
		if (!process->next_process)
		{
			if (access(full_path, F_OK | X_OK) != -1)
			{
				execute_single_command(process, full_path,
					cmd_argv, original_stdout);
				free(temp);
				return (1);
			}
			else
			{
				free(temp),
				free(full_path);
			}
		}
		i++;
	}
	k = 0;
	while (cmd_argv[k] != NULL)
	{
		free(cmd_argv[k]);
		k++;
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
		if (!process->command || (process->command && process->here_doc))
		{
			if (!process->here_doc)
				return (EXIT_FAILURE);
			else
			{
				handle_heredoc(process);
				return (EXIT_SUCCESS);
			}
		}
		find_path(process, shell);
		if (!check_command_access(process) && process->command
			&& !(starts_with_dot_slash(process->command)))
		{
			printf("zsh: command not found: %s\n", process->command);
			free(process->path_env);
			free_string_array(process->env);
			return (EXIT_FAILURE);
		}
		if (process->command)
		{
			if (ft_strncmp(process->command, "clear", 5) == 0)
				printf("\033[H\033[J");
		}
		if (starts_with_dot_slash(process->command))
		{
			execute_local_command(process);
			return (EXIT_SUCCESS);
		}
		free(process->path_env);
		free_string_array(process->env);
		return (EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
