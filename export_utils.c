#include "minishell.h"

void	only_export(t_data *shell)
{
	t_env	*current;
	int		i;
	char	*miau;

	i = 0;
	current = shell->env;
	miau = getenv("PATH");
	while (current)
	{
		printf("declare -x \"%s=%s\"\n", current->name, current->value);
		if (ft_strncmp(current->name, "MallocNanoZone",
				ft_strlen("MallocNanoZone")) == 0)
			printf("declare -x \"PATH=%s\"\n", miau);
		current = current->next;
	}
}

void	create_variable(char *variable, t_data *shell)
{
	t_env	*new_env;
	char	*name;
	char	*value;

	name = obtain_env_name(variable);
	value = obtain_env_value(variable);
	if (!check_if_exists(name, value, shell))
	{
		new_env = new_node(name, value);
		env_add_back(&shell->env, new_env);
	}
	free(value);
}

bool	check_args(char *arg, char *cmd)
{
	int		i;
	char	*name;

	(void)cmd;
	i = 0;
	name = obtain_env_name(arg);
	if (ft_isdigit(name[i]))
	{
		printf("%s: is not a valid identifier\n", name);
		return (free(name), false);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '-')
			i++;
		else
		{
			printf("%s: not a valid identifier\n", name);
			return (free(name), false);
		}
	}
	return (free(name), true);
}

int	check_if_exists(char *name, char *value, t_data *shell)
{
	t_env	*ptr;

	ptr = shell->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->name, name, ft_strlen(name)))
		{
			free(ptr->value);
			ptr->value = ft_strjoin("=", value);
			free(name);
			return (1);
		}
		ptr = ptr->next;
	}
	free(name);
	return (0);
}

t_env	*new_node(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = ft_strdup(name);
	printf("13.new_node env->name pointer = %p\n", env->name);
	env->value = ft_strjoin("=", value);
	printf("14.new_node env->value pointer = %p\n", env->value);
	env->next = NULL;
	return (env);
}
