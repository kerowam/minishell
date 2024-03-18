#include "minishell.h"

extern int	g_status;

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

void	child_process(t_process *process, char *full_path)
{
	char	**argv;

	argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
	argv = create_argv(process, argv);
	if (execve(full_path, argv, process->env) == -1)
		put_error(NOTCOMMAND, 127);
	exit(g_status);
}

void	fork_command(t_process *process, char *full_path, int input_fd,
	int output_fd)
{
	process->pid = fork();
	if (process->pid == 0)
	{
		help_child(process, input_fd, output_fd);
		child_process(process, full_path);
	}
	father_process(process, input_fd, output_fd);
}

int	execute_command(t_process *process, t_data *shell, int input_fd,
	int output_fd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	find_path(process, shell);
	if (process->env == NULL)
	{
		no_path(process, input_fd, output_fd);
		return (g_status);
	}
	while (process->env[i++] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		full_path = ft_strjoin(temp, process->command);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			fork_command(process, full_path, input_fd, output_fd);
			free_elements(temp, full_path);
			return (g_status);
		}
		free_elements(temp, full_path);
	}
	no_path(process, input_fd, output_fd);
	return (g_status);
}
