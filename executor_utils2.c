#include "minishell.h"

extern int	g_status;

void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (pipe_fd[0]);
}

void	comprobate_status(t_process *process)
{
	if (check_f_d(process) == 0)
		g_status = 1;
	else
		g_status = 0;
}
