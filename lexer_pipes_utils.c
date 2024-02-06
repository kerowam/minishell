#include "minishell.h"

int	get_pipe_nbr(char *line, int i)
{
	int		pipe_nbr;

	pipe_nbr = 0;
	while (line[i])
	{
		if (line[i] == '|')
			pipe_nbr++;
		i++;
	}
	return (pipe_nbr);
}

int	get_pipe_index(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}
