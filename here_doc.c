#include "minishell.h"

static char	**create_argv_for_command(t_process *process)
{
	int		argc;
	char	**argv;

	argc = 2;
	argv = malloc(sizeof(char *) * (argc + 1));
	argv[0] = process->command;
	argv[1] = ft_strdup(*process->args);
	argv[2] = NULL;
	return (argv);
}

static void	execute_command_with_heredoc(t_process *process, int fd_read)
{
	char	**argv;
	int		fd_pipe[2];
	pid_t	pid;

	argv = create_argv_for_command(process);
	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		execvp(process->command, argv);
		perror("Error en execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd_pipe[0]);
		write_temp_file_to_pipe(fd_pipe[1], fd_read);
		close(fd_pipe[1]);
		close(fd_read);
		waitpid(pid, NULL, 0);
	}
	free_argv(argv);
}

int	handle_heredoc(t_process *process)
{
	char	*filename;
	int		fd_write;
	int		fd_read;

	if (!process->here_doc)
		return (0);
	filename = "here_doc.tmp";
	printf("Creating temporary file: %s\n", filename);
	fd_write = create_temp_file(filename);
	read_lines_until_delimiter(fd_write, process->here_doc->content);
	close(fd_write);
	fd_read = open_temp_file_read(filename);
	if ((process->command || (process->command && process->args))
		&& process->here_doc)
		execute_command_with_heredoc(process, fd_read);
	close(fd_read);
	unlink(filename);
	return (1);
}
