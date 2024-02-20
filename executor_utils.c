#include "minishell.h"

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

int	starts_with_dot_slash(char *str)
{
	return (str && str[0] == '.' && str[1] == '/');
}

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
			process->path_env = ft_strdup(env[i] + 5);
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
				printf("Resultados de ft_split: %d: %s\n", j, process->env[j]);
				j++;
			}
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

void	execute_builtin(t_process *process, t_data *shell)
{
	(void)process;
	if (ft_strncmp(shell->echo[0], "exit\0", 5) == 0
		|| ft_strncmp(shell->echo[0], "EXIT\0", 5) == 0)
	{
		free(shell->line);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(shell->echo[0], "env\0", 4) == 0
		|| ft_strncmp(shell->echo[0], "ENV\0", 4) == 0)
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
