#include "minishell.h"

static int	create_temp_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error creating temporary file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	read_lines_until_delimiter(int fd, const char *delimiter)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
		if (!line)
		{
			perror("Error reading from standard input");
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(delimiter, line, delimiter_len) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

static int	open_temp_file_read(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening temporary file for heredoc");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	write_temp_file_to_pipe(int fd_pipe, int fd_temp)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	bytes_read = read(fd_temp, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(fd_pipe, buffer, bytes_read);
		bytes_read = read(fd_temp, buffer, sizeof(buffer));
	}
}

int	handle_heredoc(t_process *process)
{
    char *filename;
    int fd_write;
    int fd_read;
    int fd_pipe[2];
    pid_t pid;
    char **argv;
    int argc;

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
	{
		argc = 2;
		argv = malloc(sizeof(char *) * argc);
		argv[0] = process->command;
		argv[1] = *process->args;
		argv[2] = NULL;
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
	}
	close(fd_read);
	unlink(filename);
	return (1);
}
