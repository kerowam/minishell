#include "minishell.h"

void	help_child(t_process *process, int input_fd, int output_fd)
{
	redirect_infile(process);
	redirect_outfile(process);
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
}

static char	**create_argv(t_process *process, char **argv)
{
	t_list	*current;
	int		j;

	j = 1;
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
	return (argv);
}

void	father_process(t_process *process, int input_fd, int output_fd)
{
	waitpid(process->pid, &process->status, 0);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
}

void	child_process(t_process *process, char *full_path)
{
	char	**argv;

	argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
	argv = create_argv(process, argv);
	execve(full_path, argv, process->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	execute_command(t_process *process, t_data *shell, int input_fd, int output_fd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	find_path(process, shell);
	if (process->env == NULL)
	{
		no_path(process, input_fd, output_fd);
		return (EXIT_SUCCESS);
	}
	while (process->env[i++] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		full_path = ft_strjoin(temp, process->command);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			process->pid = fork();
			if (process->pid == 0)
			{
				help_child(process, input_fd, output_fd);
				child_process(process, full_path);
			}
			father_process(process, input_fd, output_fd);
			free_elements(temp, full_path);
			return (EXIT_FAILURE);
		}
		free_elements(temp, full_path);
	}
	no_path(process, input_fd, output_fd);
	return (EXIT_SUCCESS);
}
