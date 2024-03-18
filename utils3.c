#include "minishell.h"

extern int	g_status;

void	free_elements(char *temp, char *full_path)
{
	free(temp);
	free(full_path);
}

t_list	*list_next(t_list **tmp_list)
{
	if ((*tmp_list)->next)
		*tmp_list = (*tmp_list)->next;
	else
		*tmp_list = NULL;
	return (*tmp_list);
}

static void	print_exit(t_data *shell, t_process *process)
{
	printf("exit\n");
	free(shell->line);
	free_process(process);
	exit(g_status);
}

static void	print_num_exit(t_process *process)
{
	char	*arg;

	arg = process->argv->content;
	if (ft_atoi(arg) == 0 && arg[0] != '0')
		put_error2(NUMARG, 255);
	else
		g_status = ft_atoi(arg);
	exit(g_status);
}

void	exit_command(t_process *process, t_data *shell)
{
	char	*arg;

	if (process->argv)
	{
		arg = process->argv->content;
		if (process->argv->next == NULL)
			print_num_exit(process);
		if (ft_atoi(arg) == 0 && arg[0] != '0')
		{
			put_error2(NUMARG, 255);
			exit(g_status);
		}
		if (process->argv->next != NULL)
		{
			put_error2(TOMANYARG, 1);
			if (ft_atoi(arg) == 0 && arg[0] != '0')
				exit(g_status);
		}
	}
	else
		print_exit(shell, process);
}

void	no_path(t_process *process, int input_fd, int output_fd)
{
	char	*full_path;

	full_path = NULL;
	if (access(process->command, F_OK | X_OK) == 0)
		full_path = ft_strdup(process->command);
	else
	{
		put_error(NOTCOMMAND, 127);
		return ;
	}
	process->pid = fork();
	if (process->pid == 0)
	{
		help_child(process, input_fd, output_fd);
		child_process(process, full_path);
	}
	father_process(process, input_fd, output_fd);
	free(full_path);
}
