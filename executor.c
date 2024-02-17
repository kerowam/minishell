#include "minishell.h"

int	find_path(t_process *process, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			free(process->path_env);
			free_string_array(process->env);
			process->path_env = strdup(env[i] + 5);
			printf("3.process->path_env pointer: %p\n", process->path_env);
			if (!process->path_env)
			{
				perror("Error al duplicar la cadena");
				return (EXIT_FAILURE);
			}
			process->env = ft_split(process->path_env, ':');
			if (!process->env)
			{
				perror("Error al dividir la cadena");
				return (EXIT_FAILURE);
			}
			j = 0;
			while (process->env[j] != NULL)
			{
				//printf("Resultados de ft_split: %d: %s\n", j, process->env[j]);
				j++;
			}
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	check_command_access(t_process *process)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (process->env[++i] != NULL)
	{
		temp = ft_strjoin(process->env[i], "/");
		printf("4.temp pointer: %p\n", temp);
		//printf("Temp: %s\n", temp);
		full_path = ft_strjoin(temp, process->command);
		printf("5.full_path pointer: %p\n", full_path);
		//printf("Full Path: %s\n", full_path);
		free(temp);
		/*if (full_path != NULL && access(full_path, F_OK | X_OK) != -1)
		{
			free(process->command);
			process->command = full_path;
			return (1);
		}
		else
		{
   			perror("Access Error");
   			free(full_path);
		}*/
		free(full_path);
	}
	return (0);
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
		/*if (check_command_access(process))
			printf("Command path: %s\n", process->command);*/
		/*else
			printf("Command not accessible\n");*/
		return (EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

//***PARTE DE BUILTINS***//

void	execute_builtin(t_process *process, t_data *shell)
{
	(void)process;
	if (ft_strncmp(shell->line, "exit\0", 5) == 0
		|| ft_strncmp(shell->line, "EXIT\0", 5) == 0)
	{
		free(shell->line);
		//free_process(process);
		//free_env_list(shell->env);
		//free(shell);
		//free_string_array(shell->echo);
		free_echo(shell->echo);
		exit(g_exit_status); //FAILURE???
	}
	if (ft_strncmp(shell->line, "env\0", 4) == 0
		|| ft_strncmp(shell->line, "ENV\0", 4) == 0)
		env_command(shell->echo, shell);
	if (ft_strncmp(shell->line, "pwd\0", 4) == 0
		|| ft_strncmp(shell->line, "PWD\0", 4) == 0)
		pwd_command(shell);
	if (ft_strncmp(shell->echo[0], "echo\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "ECHO\0", 5) == 0)
		echo_command(shell->echo, 0);
	if (ft_strncmp(shell->line, "unset\0", 6) == 0
		|| ft_strncmp(shell->line, "UNSET\0", 6) == 0)
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
	(void)process;
	if (ft_strncmp(shell->line, "exit\0", 5) == 0
		|| ft_strncmp(shell->line, "EXIT\0", 5) == 0
		|| ft_strncmp(shell->line, "env\0", 4) == 0
		|| ft_strncmp(shell->line, "ENV\0", 4) == 0
		|| ft_strncmp(shell->line, "pwd\0", 4) == 0
		|| ft_strncmp(shell->line, "PWD\0", 4) == 0
		|| ft_strncmp(shell->echo[0], "echo\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "ECHO\0", 5) == 0
		|| ft_strncmp(shell->line, "unset\0", 6) == 0
		|| ft_strncmp(shell->line, "UNSET\0", 6) == 0
		|| ft_strncmp(*shell->echo, "cd\0", 3) == 0
		|| ft_strncmp(*shell->echo, "CD\0", 3) == 0
		|| ft_strncmp(shell->echo[0], "export\0", 7) == 0
		|| ft_strncmp(shell->echo[0], "EXPORT\0", 7) == 0)
		return (true);
	else
		return (false);
}

///***LIBERACION***///
void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
