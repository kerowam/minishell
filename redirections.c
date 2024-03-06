#include "minishell.h"

void	redirect_infile(t_process *process)
{
	int	fd;

	if (process->infile != NULL)
	{
		fd = open(process->infile, O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening input file");
			exit(EXIT_FAILURE);
		}
		printf("File '%s' opened successfully for input redirection.\n", process->infile);
		dup2(fd, STDIN_FILENO);
		printf("Input redirected successfully.\n");
		if (close(fd) == -1)
		{
			perror("Error closing input file descriptor");
			exit(EXIT_FAILURE);
		}
	}
}

void	redirect_outfile(t_process *process)
{
	int	flags;
	int	fd;

	if (process->outfile != NULL)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		if (process->appendf == 1)
		{
			flags |= O_APPEND;
		}
		fd = open(process->outfile, flags, 0666);
		if (fd == -1)
		{
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("Error redirecting output");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	redirect_outfile_append(t_process *process)
{
	int	flags;
	int	fd;

	if (process->outfile_append != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (process->appendf == 2)
			flags |= O_APPEND;
		fd = open(process->outfile_append, flags, 0666);
		if (fd == -1)
		{
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("Error redirecting output");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}
