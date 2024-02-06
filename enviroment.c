#include "minishell.h"

void	initialize_env(t_data *shell, char **env)
{
	char	**temp;

	shell->del = 0;
	printf("Ha entrado a initialize_env\n");
	shell->env = ft_calloc(1, sizeof(t_env));
	printf("Ha alojado memoria para shell->env\n");
	temp = ft_split(env[shell->del], '=');
	printf("Ha separado temp con split\n");
	if (!shell->env || !temp || !temp[0] || !temp[1])
	{
		free_temp(temp);
		return ;
	}
	printf("Ha comprobado si ambos anteriores dan error\n");
	shell->env->name = ft_strdup(temp[0]);
	printf("Ha asignado el nombre\n");
	shell->env->value = ft_strjoin("=", temp[1]);
	printf("Ha asignado valor\n");
	shell->env->index = 0;
	printf("Ha asignado el indice\n");
	shell->env->next = NULL;
	printf("Ha asignado el siguiente nodo\n");
	free_temp(temp);
	printf("Ha liberado temp\n");
	while (env[shell->del++])
	{
		printf("Ha entrado en el bucle\n");
		shell->temp_env = ft_calloc(1, sizeof(t_env));
		printf("Ha alojado memoria para shell->temp_env\n");
		temp = ft_split(env[shell->del], '=');
		printf("Ha dividido temp con split\n");
		if (!shell->temp_env || !temp || !temp[0] || !temp[1])
		{
			free_temp(temp);
			return ;
		}
		printf("Ha coprobado si fallan\n");
		add_newenv_back(&shell->env, shell->temp_env, temp);
		printf("Ha añadido la nueva variable\n");
		free_temp(temp);
		printf("Ha liberado temp\n");
	}
	add_oldpwd(shell);
	printf("Ha salido de initialize_env");
}

void	add_newenv_back(t_env **first, t_env *new, char **temp)
{
	t_env	*first_node;

	if (new == NULL || temp == NULL)
		return ;
	if (temp != NULL)
	{
		new->name = ft_strdup(temp[0]);
		new->value = ft_strjoin("=", temp[1]);
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
