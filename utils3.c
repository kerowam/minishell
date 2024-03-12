#include "minishell.h"

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

static void	print_exit(t_data *shell)
{
	printf("exit\n");
	free(shell->line);
	exit(EXIT_SUCCESS);
}

void	exit_command(t_process *process, t_data *shell)
{
	char	*arg;

	if (process->argv)
	{
		arg = process->argv->content;
		if (process->argv->next == NULL)
		{
			if (ft_atoi(arg) == 0 && arg[0] != '0')
				printf("bash: exit: a: numeric argument required.\n");
			exit(EXIT_SUCCESS);
		}
		if (ft_atoi(arg) == 0 && arg[0] != '0')
		{
			printf("bash: exit: a: numeric argument required.\n");
			exit(EXIT_FAILURE);
		}
		if (process->argv->next != NULL)
		{
			printf("bash: exit: too many arguments\n");
			if (ft_atoi(arg) == 0 && arg[0] != '0')
				exit(EXIT_FAILURE);
		}
	}
	else
		print_exit(shell);
}

void	no_path(t_process *process, int input_fd, int output_fd)
{
	char	*full_path;

	full_path = NULL;
	if (access(process->command, F_OK | X_OK) == 0)
		full_path = ft_strdup(process->command);
	else
	{
		printf("Command not found: %s\n", process->command);
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
