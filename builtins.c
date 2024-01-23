
#include "minishell.h"

int	env_command(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	pwd_command(void)
{
	char	*current_directory;

	current_directory = getenv("PWD");
	if (current_directory != NULL)
		printf("%s\n", current_directory);
	else
	{
		perror("getenv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	echo_command(char **args)
{
	int	i;
	int	flag_n;

	i = 1;
	flag_n = 0;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "-n", 2) == 0)
		{
			flag_n = 1;
			i++;
		}
		else
			break ;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		i++;
		if (args[i] != NULL)
			printf(" ");
	}
	if (!flag_n)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	unset_command_with_args(char **args, char ***envp)
{
	int		i;
	char	*current_var;
	int		j;

	i = 0;
	while (args[i] != NULL)
	{
		current_var = args[i];
		j = 0;
		while ((*envp)[j] != NULL)
		{
			if (ft_strncmp((*envp)[j], current_var,
				ft_strlen(current_var)) == 0)
			{
				while ((*envp)[j++] != NULL)
				{
					(*envp)[j] = (*envp)[j + 1];
				}
				break ;
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	unset_command(char **args, char ***envp)
{
	if (args[1] == NULL)
	{
		printf("Unset: missing argument\n");
		return (EXIT_FAILURE);
	}
	else
		return (unset_command_with_args(args, envp));
}
