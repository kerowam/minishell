#include "minishell.h"

void	execute_processes(t_process *process)
{
	t_process	*current_process;
	char		**args;

	current_process = process;
	while (current_process != NULL)
	{
		if (!execute_builtin(current_process))
		{
			process->pid = fork();
			if (process->pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (process->pid == 0)
			{
				// Proceso hijo, ejecucion del comando
				// Redirecciones, execve, etc)
				if (current_process->infile != NULL)
				{
					current_process->inf = open(current_process->infile,
							O_RDONLY);
					if (current_process->inf == -1)
					{
						perror("open");
						exit(EXIT_FAILURE);
					}
					dup2(current_process->inf, STDIN_FILENO);
					close(current_process->inf);
				}
				if (current_process->outfile != NULL)
				{
					current_process->outf = open(current_process->outfile,
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (current_process->outf == -1)
					{
						perror("open");
						exit(EXIT_FAILURE);
					}
					dup2(current_process->outf, STDOUT_FILENO);
					close(current_process->outf);
				}
				args = convert_args_list_to_array(current_process->argv);
				execvp(current_process->command, args);
				perror("execvp");
				free(args);
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(process->pid, &process->status, 0);
				// Manejar estado proceso hijo (status)
				// Salida, señales, etc)
			}
		}
		current_process = current_process->next_process;
	}
	while (process != NULL)
	{
		waitpid(process->pid, &process->status, 0);
		process = process->next_process;
	}
}

char	**convert_args_list_to_array(t_list *argv_list)
{
	char	**argv_array;
	int		i;

	argv_array = malloc((ft_lstsize(argv_list) == 1) * sizeof(char *));
	if (!argv_array)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (argv_list != NULL)
	{
		argv_array[i] = argv_list->content;
		argv_list = argv_list->next;
		i++;
	}
	argv_array[i] = NULL;
	return (argv_array);
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

bool	execute_builtin(t_process *process)
{
	t_data	*shell;

	(void)process;
	shell = NULL;
	shell->echo = ft_split(shell->line, ' ');
	if (ft_strncmp(shell->line, "exit\0", 5) == 0
		|| ft_strncmp(shell->line, "EXIT\0", 5) == 0)
	{
		free(shell->line);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(shell->line, "env\0", 4) == 0
		|| ft_strncmp(shell->line, "ENV\0", 4) == 0)
	{
		env_command(shell->echo, shell);
		return (true);
	}
	if (ft_strncmp(shell->line, "pwd\0", 4) == 0
		|| ft_strncmp(shell->line, "PWD\0", 4) == 0)
	{
		pwd_command(shell);
		return (true);
	}
	if (ft_strncmp(shell->echo[0], "echo\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "ECHO\0", 5) == 0)
	{
		echo_command(shell->echo, 0);
		return (true);
	}
	if (ft_strncmp(shell->line, "unset\0", 6) == 0
		|| ft_strncmp(shell->line, "UNSET\0", 6) == 0)
	{
		unset_command(shell, shell->echo[1]);
		return (true);
	}
	if (ft_strncmp(*shell->echo, "cd\0", 3) == 0
		|| ft_strncmp(shell->line, "CD\0", 3) == 0)
	{
		cd_command(shell->echo, shell);
		return (true);
	}
	if (ft_strncmp(shell->echo[0], "export\0", 7) == 0
		|| ft_strncmp(shell->echo[0], "EXPORT\0", 7) == 0)
	{
		export_command(shell->echo, shell);
		return (true);
	}
	return (false);
}
