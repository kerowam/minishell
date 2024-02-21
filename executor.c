#include "minishell.h"

void	redirect_input(t_process *process)
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
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("Error redirecting input");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	redirect_output(t_process *process)
{
	int	flags;
	int	fd;

	fd = -1;
	if (process->outfile != NULL || process->outfile_append != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (process->appendf == 1)
		{
			flags |= O_TRUNC;
			fd = open(process->outfile, flags, 0666);
		}
		else if (process->appendf == 2)
		{
			if (process->outfile != NULL)
				fd = open(process->outfile, O_WRONLY
						| O_CREAT | O_APPEND, 0666);
			else
			{
				flags |= O_APPEND;
				fd = open(process->outfile_append, flags, 0666);
			}
		}
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
	}
	if (fd != -1)
		close(fd);
}



int	check_command_access(t_process *process)
{
	int		i;
	char	*full_path;
	char	*temp;
	char	**cmd_argv;
	t_list	*current;
	int		j;
	int		k;
	int		original_stdout;

	i = 0;
	original_stdout = dup(STDOUT_FILENO);
	cmd_argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
	if (!cmd_argv)
	{
		perror("Error allocating memory for cmd_argv");
		exit(EXIT_FAILURE);
	}
	while (process->env[++i] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		full_path = ft_strjoin(temp, process->command);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			printf("ACCESO\n");
			redirect_input(process);
			redirect_output(process);
			cmd_argv[0] = ft_strdup(process->command);
			current = process->argv;
			j = 1;
			while (current)
			{
				cmd_argv[j] = ft_strdup(current->content);
				current = current->next;
				j++;
			}
			cmd_argv[j] = NULL;
			process->pid = fork();
			if (process->pid == -1)
			{
				perror("Error al crear el proceso hijo");
				exit(EXIT_FAILURE);
			}
			else if (process->pid == 0)
			{
				execve(full_path, cmd_argv, process->env);
				perror("Error al ejecutar el comando\n");
				exit(EXIT_FAILURE);
			}
			waitpid(process->pid, &process->status, 0);
			dup2(original_stdout, STDOUT_FILENO);
			close(original_stdout);
			free(temp);
			free(full_path);
			k = 0;
			while (k <= j)
			{
				free(cmd_argv[k]);
				k++;
			}
			free(cmd_argv);
			return (1);
		}
		else
		{
			printf("NO ACCESO\n");
			free(full_path);
		}
		free(temp);
	}
	free(cmd_argv);
	return (0);
}

void	execute_local_command(t_process *process)
{
	char	full_path[1000];
	char	*cwd;
	char	**cmd_argv;
	t_list	*current;
	int		j;

	cwd = getcwd(NULL, 0);
	ft_strlcpy(full_path, cwd, sizeof(full_path));
	ft_strlcat(full_path, "/", sizeof(full_path));
	ft_strlcat(full_path, process->command, sizeof(full_path));
	if (access(full_path, F_OK | X_OK) != -1)
	{
		printf("ACCESO\n");
		printf("Command path: %s\n", full_path);
		cmd_argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
		if (!cmd_argv)
		{
			perror("Error al asignar memoria para cmd_argv");
			free(cwd);
			exit(EXIT_FAILURE);
		}
		cmd_argv[0] = ft_strdup(process->command);
		current = process->argv;
		j = 1;
		while (current)
		{
			cmd_argv[j] = ft_strdup(current->content);
			current = current->next;
			j++;
		}
		cmd_argv[j] = NULL;
		process->pid = fork();
		if (process->pid == -1)
		{
			perror("Error al crear el proceso hijo");
			free(cwd);
			exit(EXIT_FAILURE);
		}
		else if (process->pid == 0)
		{
			execve(full_path, cmd_argv, process->env);
			perror("Error al ejecutar el comando\n");
			exit(EXIT_FAILURE);
		}
		waitpid(process->pid, &process->status, 0);
		free(cmd_argv);
		free(cwd);
		return ;
	}
	else
		printf("NO ACCESO\n");
	free(cwd);
}

int	main_executor(t_data *shell, char **env, t_process *process)
{
	if (!process)
		exit(EXIT_FAILURE);
	if (is_builtin(process, shell))
		execute_builtin(process, shell);
	else if (!is_builtin(process, shell))
	{
		find_path(process, env);
		printf("OUTFILE: %s\n", process->outfile);
		printf("OUTFILE_APPEND: %s\n", process->outfile_append);
		printf("OUTF: %d\n", process->outf);
		check_command_access(process);
		if (ft_strncmp(process->command, "clear", 5) == 0)
			printf("\033[H\033[J");
		if (starts_with_dot_slash(process->command))
			execute_local_command(process);
		return (EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
