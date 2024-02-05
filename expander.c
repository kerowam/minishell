#include "minishell.h"

int	get_len_word(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] != ' ' && str[i])
	{
		i++;
		len++;
	}
	return (len);
}

char	*get_expanded_value(t_env *env, char *key)
{
	char	*value;
	t_env	*tmp;
	char	*name;

	tmp = (t_env *)malloc(sizeof(t_env));
	*tmp = *env;
	name = NULL;
	while (tmp->name)
	{
		name = ft_strdup(tmp->name);
		printf("name: %s\n", name);
		printf("key: %s\n", key);
		if (*key == *name)
		{
			value = ft_strdup(tmp->value);
			return (value);
		}
		free(name);
		if (tmp->next)
			*tmp = *tmp->next;
		else
			break ;
	}
	value = ft_strdup(""); //Comprobar que así funciona o buscar alternativa.
	return (value);
	//return (NULL);
}

char	*set_key(char *str, int i)
{
	size_t	len;
	char	*tmp;

	len = get_len_word(str, i);
	tmp = ft_substr(str, i, len);
	return (tmp);
}

char	*expand(char *str, t_env *env)
{
	int		i;
	char	*tmp;
	char	*value;
	char	*end_str;
	int		start;

	i = 0;
	end_str = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			tmp = set_key(str, i);
			value = get_expanded_value(env, tmp);
			if (!end_str)
				end_str = ft_strdup(value);
			else
				end_str = ft_strjoin(end_str, value);
			free(tmp);
			free(value);
			while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\"')
				i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			tmp = ft_substr(str, start, i - start);
			if (!end_str)
				end_str = ft_strdup(tmp);
			else
				end_str = ft_strjoin(end_str, tmp);
			free(tmp);
			//i++;
		}
	}
	return (end_str);
}

t_list	**expander(t_env *env, t_list **line_splited)
{
	t_env	*tmp_env;
	t_list	**tmp_list;
	char	*tmp_str;

	tmp_env = (t_env *)malloc(sizeof(t_env));
	*tmp_env = *env;
	tmp_list = (t_list **)malloc(sizeof(t_list *));
	*tmp_list = *line_splited;
	while (*tmp_list)
	{
		tmp_str = (*tmp_list)->content;
		if (tmp_str[0] == '\'' || ft_strchr(tmp_str, '$') == 0)
		{
			if ((*tmp_list)->next)
				*tmp_list = (*tmp_list)->next;
			else
				break ;
		}
		else
		{
			if (ft_strchr(tmp_str, '$') != 0)
				(*tmp_list)->content = expand(tmp_str, tmp_env);
			if ((*tmp_list)->next)
				*tmp_list = (*tmp_list)->next;
			else
				break ;
		}
	}
	return (line_splited);
}
