#include "minishell.h"

void	initialize_env(t_data *shell, char **env)
{
	shell->del = 0;
	shell->env = ft_calloc(1, sizeof(t_env));
	shell->temp = ft_split(env[shell->del], '=');
	if (!shell->env || !shell->temp || !shell->temp[0] || !shell->temp[1])
		return ;
	free(shell->temp[0]);
	shell->env->name = ft_strdup(shell->temp[0]);
	free(shell->temp[1]);
	shell->env->value = ft_strdup(shell->temp[1]);
	shell->env->index = 0;
	shell->env->next = NULL;
	free(shell->temp);
	while (env[shell->del++])
	{
		shell->temp_env = ft_calloc(1, sizeof(t_env));
		if (env[shell->del])
			shell->temp = ft_split(env[shell->del], '=');
		if (!shell->temp_env || !shell->temp
			|| !shell->temp[0] || !shell->temp[1])
			return ;
		add_newenv_back(&shell->env, shell->temp_env, shell->temp);
		free(shell->temp[0]);
		free(shell->temp);
	}
	add_oldpwd(shell);
}

void	add_newenv_back(t_env **first, t_env *new, char **temp)
{
	t_env	*first_node;

	if (new == NULL || temp == NULL)
		return ;
	if (temp != NULL)
	{
		new->name = ft_strdup(temp[0]);
		new->value = ft_strdup(temp[1]);
		new->index = 0;
		new->next = NULL;
	}
	first_node = *first;
	if (*first == NULL)
	{
		*first = new;
		return ;
	}
	while (first_node->next != NULL)
		first_node = first_node->next;
	first_node->next = new;
}

void	add_oldpwd(t_data *shell)
{
	t_env	*aux;
	t_env	*new;
	int		exist;
	char	current_dir[500];

	getcwd(current_dir, 500);
	aux = shell->env;
	exist = 0;
	while (aux)
	{
		if (!ft_strncmp(aux->name, "OLDPWD", ft_strlen("OLDPWD")))
			exist = 1;
		aux = aux->next;
	}
	if (!exist)
	{
		new = ft_calloc(1, sizeof(t_env));
		new->name = ft_strdup("OLDPWD");
		new->value = ft_strjoin("=", current_dir);
		new->next = NULL;
		add_newenv_back(&shell->env, new, NULL);
	}
}

char	*obtain_env_name(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, 0, i));
}

char	*obtain_env_value(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, i + 1, ft_strlen(fullenv) - i));
}