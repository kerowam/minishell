#include "minishell.h"

static int	create_temp_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

int	handle_heredoc(t_process *process)
{
	char	*filename;
	int		fd_write;
	char	*str_fd;
	int		fd_read;

	if (!process->here_doc)
		return (0);
	filename = "here_doc.tmp";
	fd_write = create_temp_file(filename);
	read_lines_until_delimiter(fd_write, process->here_doc->content);
	close(fd_write);
	fd_read = open_temp_file_read(filename);
	str_fd = ft_itoa(fd_read);
	process->infile = str_fd;
	return (1);
}
