#include "minishell.h"

extern int	g_status;

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

void	pwd_command(t_data *shell, t_process *process)
{
	char	*path;

	(void)process;
	(void)shell;
	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	if (path)
	{
		printf("%s\n", path);
		free(path);
		g_status = 0;
	}
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

void	export_command(t_process *process, t_data *shell)
{
	if (process->command && !process->args)
		only_export(shell);
	else
	{
		while (process->argv->content)
		{
			if (check_args(process->argv->content, process->argv->content))
				create_variable(process->argv->content, shell);
			break ;
		}
	}
}
