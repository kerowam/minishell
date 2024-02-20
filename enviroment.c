#include "minishell.h"

void	initialize_env(t_data *shell, char **env)
{
	char	*miau;

	miau = getenv("PATH");
	if (!miau)
		exit(EXIT_FAILURE);
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
	while (env[shell->del++] != NULL)
	{
		shell->temp_env = ft_calloc(1, sizeof(t_env));
		if (env[shell->del])
			shell->temp = ft_split(env[shell->del], '=');
		if (!shell->temp_env || !shell->temp
			|| !shell->temp[0] || !shell->temp[1])
			return ;
		if (ft_strncmp(shell->temp[0], "PATH", 4) == 0)
		{
			free(shell->temp[1]);
			free(shell->temp[0]);
			free(shell->temp);
			add_path_to_env(shell, miau);
			continue ;
		}
		add_newenv_back(&shell->env, shell->temp_env, shell->temp);
	}
	free(miau);
}

void	add_newenv_back(t_env **first, t_env *new, char **temp)
{
	t_env	*first_node;

	if (new == NULL || temp == NULL)
		return ;
	if (temp != NULL)
	{
		free(temp[0]);
		new->name = ft_strdup(temp[0]);
		free(temp[1]);
		new->value = ft_strdup(temp[1]);
		new->index = 0;
		new->next = NULL;
		free(temp);
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

void	add_path_to_env(t_data *shell, char *path)
{
	t_env	*new;
	t_env	*current;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	new->name = strdup("PATH");
	if (!new->name)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	new->value = strdup(path);
	if (!new->value)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	new->index = 0;
	new->next = NULL;
	current = shell->env;
	if (current)
	{
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
	}
	current = shell->env;
	if (!current)
		shell->env = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	shell->env_count++;
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
