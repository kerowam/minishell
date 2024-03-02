#include "minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
	{
		printf("Warning: Attempting to free a NULL array.\n");
		return ;
	}
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	starts_with_dot_slash(char *str)
{
	return (str && str[0] == '.' && str[1] == '/');
}

int	find_path(t_process *process, t_data *shell)
{
	t_env	*current_env;

	current_env = shell->env;
	while (current_env != NULL)
	{
		if (ft_strncmp(current_env->name, "PATH", 4) == 0)
		{
			process->path_env = ft_strdup(current_env->value);
			process->env = ft_split(process->path_env, ':');
			if (!process->env || !process->path_env)
			{
				perror("Error al dividir o duplicar la cadena");
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		current_env = current_env->next;
	}
	return (EXIT_FAILURE);
}

void	execute_builtin(t_process *process, t_data *shell)
{
	if (ft_strncmp(shell->echo[0], "exit\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "EXIT\0", 5) == 0)
	{
		printf("exit\n");
		free_echo(shell->echo);
		free(shell->line);
		//free(shell);
		/*if (process)
		{
			free_process(process);
		}*/
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(shell->echo[0], "env\0", 4) == 0
		|| ft_strncmp(shell->echo[0], "ENV\0", 4) == 0)
		env_command(shell);
	if (ft_strncmp(shell->line, "pwd\0", 4) == 0
		|| ft_strncmp(shell->line, "PWD\0", 4) == 0)
		pwd_command(shell);
	if (ft_strncmp(shell->echo[0], "echo\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "ECHO\0", 5) == 0)
		echo_command(shell->echo, 0);
	if (ft_strncmp(&process->command[0], "unset\0", 6) == 0
		|| ft_strncmp(&process->command[0], "UNSET\0", 6) == 0)
		unset_command(shell, shell->echo[1]);
	if (ft_strncmp(*shell->echo, "cd\0", 3) == 0
		|| ft_strncmp(shell->line, "CD\0", 3) == 0)
		cd_command(shell->echo, shell);
	if (ft_strncmp(shell->echo[0], "export\0", 7) == 0
		|| ft_strncmp(shell->echo[0], "EXPORT\0", 7) == 0)
		export_command(shell->echo, shell);
}

bool	is_builtin(t_process *process, t_data *shell)
{
	bool	is_builtin_command;
	char	*trimmed_command;

	trimmed_command = ft_strtrim(shell->line, " \t\n\r\f\v");
	if (!process->command)
		return (false);
	is_builtin_command = false;
	if (ft_strcmp(process->command, "exit") == 0
		|| ft_strcmp(process->command, "EXIT") == 0
		|| ft_strcmp(process->command, "env") == 0
		|| ft_strcmp(process->command, "ENV") == 0
		|| ft_strcmp(shell->line, "pwd") == 0
		|| ft_strcmp(shell->line, "PWD") == 0
		|| ft_strcmp(trimmed_command, "echo") == 0
		|| ft_strcmp(trimmed_command, "ECHO") == 0
		|| ft_strcmp(&process->command[0], "unset") == 0
		|| ft_strcmp(&process->command[0], "UNSET") == 0
		|| ft_strcmp(*shell->echo, "cd") == 0
		|| ft_strcmp(*shell->echo, "CD") == 0
		|| ft_strcmp(process->command, "export") == 0
		|| ft_strcmp(process->command, "EXPORT") == 0)
		is_builtin_command = true;
	free(trimmed_command);
	return (is_builtin_command);
}
