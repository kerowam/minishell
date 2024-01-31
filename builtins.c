#include "minishell.h"

void	env_command(t_data *shell)
{
	t_env	*current_env;

	current_env = shell->env;
	while (current_env != NULL)
	{
		printf("%s%s\n", current_env->name, current_env->value);
		current_env = current_env->next;
	}
}

void	pwd_command(t_data *shell)
{
	if (getcwd(shell->cwd, sizeof(shell->cwd)) != NULL)
		printf("%s\n", shell->cwd);
	else
		perror("getcwd");
}

void	echo_command(char **str, int exists)
{
	int	str_size;
	int	i;

	str_size = 0;
	while (str[str_size])
		str_size++;
	if (str_size > 1)
	{
		str_size = 0;
		while (str[++str_size] && !ft_strncmp(str[str_size], "-n", 2))
			exists = 1;
		while (str[str_size])
		{
			i = -1;
			while (str[str_size][++i])
				if (str[str_size][i] != '\'' && str[str_size][i] != '\"')
					printf("%c", str[str_size][i]);
			if (str[str_size + 1] || str[str_size][0] == '\0')
				printf(" ");
			str_size++;
		}
	}
	if (exists == 0)
		printf("\n");
}

void	unset_command(t_data *shell, char *name)
{
	t_env	*aux;
	t_env	*delete;
	t_env	*previous;

	if (!name)
		return ;
	aux = shell->env;
	previous = NULL;
	while (aux)
	{
		if (ft_strncmp(aux->name, name, ft_strlen(name)))
		{
			delete = aux;
			if (previous)
				previous->next = aux->next;
			else
				shell->env = aux->next;
			free(delete->name);
			free(delete->value);
			free(delete);
			break ;
		}
		previous = aux;
		aux = aux->next;
	}
}

void	export_command(char **cmd, t_data *shell)
{
	int	i;

	i = 1;
	if (!cmd[1])
		ft_non_arg_export(shell);
	else
	{
		while (cmd[i])
		{
			if (input_checker(cmd[i], cmd[0]))
				save_variable(cmd[i], shell);
			i++;
		}
	}
}
