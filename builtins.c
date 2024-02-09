#include "minishell.h"

void	env_command(char **cmd, t_data *shell)
{
	t_env	*current_env;

	current_env = shell->env;
	if (cmd[1])
	{
		printf("\033[0;33mconchita: env: \033[0m\n");
		printf("\033[0;33mNo arguments supported\n\033[0m\n");
		return ;
	}
	while (current_env)
	{
		if (current_env->value[0])
			printf("%s=%s\n", current_env->name, current_env->value);
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
	t_env	*prov;
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	prov = shell->env;
	prev = NULL;
	while (prov)
	{
		if (!ft_strncmp(prov->name, name, ft_strlen(name)))
		{
			del = prov;
			if (prev)
				prev->next = prov->next;
			else
				shell->env = prov->next;
			free(del->name);
			free(del->value);
			free(del);
			break ;
		}
		prev = prov;
		prov = prov->next;
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
