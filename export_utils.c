#include "minishell.h"

void	ft_non_arg_export(t_data *shell)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		printf("declare -x %s%s\n", current->name, current->value);
		current = current->next;
	}
}

void	save_variable(char *variable, t_data *shell)
{
	t_env	*new_env;
	char	*name;
	char	*value;

	name = ft_get_env_name(variable);
	value = ft_get_env_value(variable);
	if (!check_variable(name, value, shell))
	{
		new_env = ft_new_env_node(name, value);
		env_add_back(&shell->env, new_env);
	}
	free(name);
	free(value);
}

bool	input_checker(char *arg, char *cmd)
{
	int		i;
	char	*name;

	(void)cmd;
	i = 0;
	name = ft_get_env_name(arg);
	if (ft_isdigit(name[i]))
	{
		printf("\033[0;33m`%s': is not a valid identifier\n\033[0m", name);
		return (free(name), false);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '-')
			i++;
		else
		{
			printf("\033[0;33m`%s': not a valid identifier\n\033[0m", name);
			return (free(name), false);
		}
	}
	return (free(name), true);
}

int	check_variable(char *name, char *value, t_data *shell)
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
	return (0);
}

t_env	*ft_new_env_node(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = ft_strdup(name);
	env->value = ft_strjoin("=", value);
	env->next = NULL;
	return (env);
}
