#include "minishell.h"

int	execute_command(t_process *process, int input_fd, int output_fd)
{
	int		i;
	int		j;
	char	*temp;
	char	*full_path;
	char	**argv;
	t_list	*current;
	int		k;

	i = 0;
	argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
	while (process->env[i] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		full_path = ft_strjoin(temp, process->command);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			argv[0] = ft_strdup(process->command);
			current = process->argv;
			j = 1;
			while (current)
			{
				argv[j] = ft_strdup(current->content);
				current = current->next;
				j++;
			}
			argv[j] = NULL;
			process->pid = fork();
			if (process->pid == 0)
			{
				redirect_infile(process);
				redirect_outfile(process);
				redirect_outfile_append(process);
				if (input_fd != STDIN_FILENO)
				{
					dup2(input_fd, STDIN_FILENO);
					close(input_fd);
				}
				if (output_fd != STDOUT_FILENO)
				{
					dup2(output_fd, STDOUT_FILENO);
					close(output_fd);
				}
				execve(full_path, argv, process->env);
				perror("execve");
				exit(EXIT_FAILURE);

			}
			waitpid(process->pid, &process->status, 0);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (output_fd != STDOUT_FILENO)
				close(output_fd);
			free(temp);
			free(full_path);
			k = 0;
			while (argv[k] != NULL)
			{
				free(argv[k]);
				k++;
			}
			free(argv);
		}
		else
		{
			free(full_path);
			free(temp);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	is_single_command(t_process *process)
{
	int	i;

	i = 1;
	while (process->next_process)
	{
		i++;
		process = process->next_process;
	}
	if (i == 1)
		return (true);
	else
		return (false);
}

int	main_executor(t_data *shell, t_process *process)
{
	if (!process)
		return (EXIT_FAILURE);
	else
	{
		if (!process->command || (process->command && process->here_doc))
		{
			if (!process->here_doc)
				return (EXIT_FAILURE);
			else
				handle_heredoc(process);
			return (EXIT_SUCCESS);
		}
		if (process->command)
		{
			if (ft_strncmp(process->command, "clear", 5) == 0)
				printf("\033[H\033[J");
		}
		if (is_single_command(process))
		{
			find_path(process, shell);
			execute_command(process, STDIN_FILENO, STDOUT_FILENO);
			free_commands(process);
		}
		else if (!is_single_command(process))
			execute_multiple_commands(process, shell);
		if (starts_with_dot_slash(process->command))
			execute_local_command(process);
	}
	return (EXIT_SUCCESS);
}

void	execute_multiple_commands(t_process *process, t_data *shell)
{
	t_process	*current_process;
	int			input_fd;
	int			pipe_fd[2];

	current_process = process;
	input_fd = STDIN_FILENO;
	while (current_process)
	{
		if (current_process->next_process)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			find_path(current_process, shell);
			execute_command(current_process, input_fd, pipe_fd[1]);
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
			free_commands(current_process);
			current_process = current_process->next_process;
		}
		else
		{
			find_path(current_process, shell);
			execute_command(current_process, input_fd, STDOUT_FILENO);
			free_commands(current_process);
			current_process = current_process->next_process;
		}
	}
	while (wait(NULL) > 0)
		;
}
