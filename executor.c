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
				redirect_outfile_append(process);
				redirect_outfile(process);
				redirect_infile(process);
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
	t_process	*current_process;
	int			input_fd;
	int			pipe_fd[2];
	id_t		i;

	if (!process)
		return (EXIT_FAILURE);
	else
	{
		if (is_single_command(process))
		{
			find_path(process, shell);
			execute_command(process, STDIN_FILENO, STDOUT_FILENO);
			free(process->path_env);
			free_string_array(process->env);
		}
		else if (!is_single_command(process))
		{
			current_process = process;
			input_fd = STDIN_FILENO;
			i = 1;
			while (current_process)
			{
				find_path(current_process, shell);
				printf("Ejecutando comando %d: %s\n", i, current_process->command);
				if (current_process->next_process)
				{
					if (pipe(pipe_fd) == -1)
					{
						perror("pipe");
						exit(EXIT_FAILURE);
					}
				}
				if (current_process->next_process)
					execute_command(current_process, input_fd, pipe_fd[1]);
				else
					execute_command(current_process, input_fd, STDOUT_FILENO);
				if (current_process->next_process)
				{
					close(pipe_fd[1]);
					input_fd = pipe_fd[0];
				}
				current_process = current_process->next_process;
				i++;
			}
			while (wait(NULL) > 0)
				;
			free(process->path_env);
			free_string_array(process->env);
		}
	}
	return (EXIT_SUCCESS);
}
