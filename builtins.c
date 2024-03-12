#include "minishell.h"

void	env_command(t_data *shell)
{
	t_env	*head;

	head = shell->env;
	while (head)
	{
		if (head != NULL && head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
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
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	aux = shell->env;
	prev = NULL;
	while (aux)
	{
		if (strcmp(aux->name, name) == 0)
		{
			del = aux;
			if (prev)
				prev->next = aux->next;
			else
				shell->env = aux->next;
			free(del->name);
			free(del->value);
			free(del);
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}

void	export_command(char **cmd, t_data *shell)
{
	int	i;

	i = 1;
	if (!cmd[1])
		only_export(shell);
	else
	{
		while (cmd[i])
		{
			if (check_args(cmd[i], cmd[0]))
				create_variable(cmd[i], shell);
			i++;
		}
	}
}
