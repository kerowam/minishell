#include "minishell.h"

extern int	g_status;

int	execute_single_process(t_process *process, t_data *shell,
	int input_fd, int output_fd)
{
	if (process->command == NULL || process->command[0] == '\0')
	{
		if (process->next_process != NULL)
			free_commands(process);
		return (g_status);
	}
	if (is_builtin(process, shell))
		execute_builtin(process, shell);
	else
	{
		if (!execute_command(process, shell, input_fd, output_fd))
		{
			if (process->next_process != NULL)
				free_commands(process);
			return (g_status);
		}
	}
	return (g_status);
}

void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		put_error(PIPEERROR, 1);
		exit(g_status);
	}
	return (pipe_fd[0]);
}

void	execute_multiple_commands(t_process *process, t_data *shell)
{
	int	input_fd;
	int	pipe_fd[2];

	input_fd = STDIN_FILENO;
	while (process)
	{
		if ((process->next_process && process->outfile == NULL))
		{
			create_pipe(pipe_fd);
			if (!execute_single_process(process, shell, input_fd, pipe_fd[1]))
				break ;
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
			free_commands(process);
			process = process->next_process;
		}
		else
		{
			if (g_status != 258)
			{
				execute_single_process(process, shell, input_fd, STDOUT_FILENO);
				//free_commands(process);
			}
			process = process->next_process;
		}
	}
	wait_for_children();
}

int	main_executor(t_data *shell, t_process *process)
{
	if (!process)
		return (g_status);
	//if (!is_builtin(process, shell))
	//{
		if (!process->command || (process->command && process->here_doc))
		{
			if (!process->here_doc)
			{
				g_status = 2;
				return (g_status);
			}
			else
			{
				handle_heredoc(process);
				return (g_status);
			}
		}
		if (process->command)
		{
			if (ft_strncmp(process->command, "clear", 5) == 0)
				printf("\033[H\033[J");
		}
		execute_multiple_commands(process, shell);
	//}
	return (g_status);
}

