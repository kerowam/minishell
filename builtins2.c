#include "minishell.h"

char	*update_variable(char *variable, char *new_value)
{
	char	*var_name;
	char	*updated_variable;
	size_t	var_len;
	size_t	new_len;

	updated_variable = NULL;
	if (variable != NULL)
	{
		var_name = ft_strchr(variable, '=') + 1;
		var_len = ft_strlen(var_name);
		new_len = ft_strlen(new_value);
		if (new_len <= var_len)
		{
			ft_strlcpy((char *)var_name, new_value, var_len);
			updated_variable = variable;
		}
		else
		{
			updated_variable = malloc(new_len + var_len + 1);
			if (updated_variable != NULL)
				ft_strlcpy((char *)var_name, new_value, var_len + new_len + 1);
			free(updated_variable);
		}
	}
	return (updated_variable);
}

void	update_pwd(char ***envp, char *new_pwd)
{
	char	**current;

	current = *envp;
	while (*current)
	{
		if (ft_strncmp(*current, "PWD=", 4) == 0
			|| ft_strncmp(*current, "OLDPWD=", 7) == 0)
		{
			if (new_pwd != NULL)
				update_variable(*current, new_pwd);
		}
		++current;
	}
}

void	cd_command(char *path, char ***envp)
{
	char	*previous_directory;
	char	*current_directory;

	if (path == NULL || *path == '\0')
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			perror("Error getting HOME directory");
			return ;
		}
	}
	previous_directory = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("Error changing directory");
		free(previous_directory);
		return ;
	}
	current_directory = getcwd(NULL, 0);
	update_pwd(envp, current_directory);
	free(current_directory);
	free(previous_directory);
}
