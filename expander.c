#include "minishell.h"

extern int	g_status;

char	*get_expanded_value(t_env *env, char *key)
{
	char	*value;
	t_env	**tmp;
	char	*name;

	tmp = NULL;
	tmp = init_tmp_env(tmp);
	*tmp = env;
	name = NULL;
	if (ft_strcmp(key, "?") == 0)
	{
		value = ft_itoa(g_status);
		free(tmp);
		return (value);
	}
	while (*tmp != NULL)
	{
		name = ft_strdup((*tmp)->name);
		if (ft_strncmp(key, name, ft_strlen(name)) == 0)
		{
			value = ft_strdup((*tmp)->value);
			return (free(tmp), free (name), value);
		}
		free(name);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			*tmp = NULL;
	}
	value = ft_strdup("");
	return (free(tmp), value);
}

char	*expand_value(char *str, int i, t_env *env, char *end_str)
{
	char	*value;
	char	*tmp;

	tmp = set_key(str, i);
	if (ft_strncmp(tmp, "$", 1) != 0)
		value = get_expanded_value(env, tmp);
	else
		value = ft_strdup(tmp);
	if (!end_str)
		end_str = ft_strdup(value);
	else
		end_str = ft_strjoin(end_str, value);
	/*if (tmp != NULL)
	free(tmp);*/
	tmp = NULL;
	free(value);
	value = NULL;
	return (end_str);
}

char	*join_expand(char *str, int i, char *end_str)
{
	char	*tmp;
	int		start;

	start = i;
	while (str[i] && str[i] != '$')
	{
		if (str[i] == '\'')
			i = search_end_quoted_string(str[i], str, i + 1);
		else
			i++;
	}
	tmp = ft_substr(str, start, i - start);
	if (!end_str)
		end_str = ft_strdup(tmp);
	else
		end_str = ft_strjoin(end_str, tmp);
	free(tmp);
	tmp = NULL;
	return (end_str);
}

char	*expand(char *str, t_env *env)
{
	int		i;
	char	*end_str;

	i = 0;
	end_str = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			i = search_end_quoted_string(str[i], str, i + 1);
		else if (str[i] == '$')
		{
			i++;
			//if (str[i] == '?')
			//if (str[i] == '\"' || str[i] == ' ' || !str[i])
		
			end_str = expand_value(str, i, env, end_str);
			while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\"')
				i++;
		}
		else
		{
			end_str = join_expand(str, i, end_str);
			while (str[i] && str[i] != '$' && str[i] != '\'')
				i++;
		}
	}
	if (end_str == NULL)
		end_str = ft_strdup(str);
	return (end_str);
}

void	expander(t_env *env, t_list **line_splited)
{
	t_env	**tmp_env;
	t_list	**tmp_list;
	char	*tmp_str;

	tmp_env = (t_env **)ft_calloc(0, sizeof(t_env *));
	tmp_list = (t_list **)ft_calloc(0, sizeof(t_list *));
	if (tmp_env == NULL || tmp_list == NULL)
	{
		put_error(MEMPROBLEM, 1);
		return ;
	}
	*tmp_env = env;
	*tmp_list = *line_splited;
	while (*tmp_list != NULL)
	{
		tmp_str = ft_strdup((*tmp_list)->content);
		if (tmp_str == NULL)
			return ;
		if (ft_strchr(tmp_str, '$') != 0)
		{
			free((*tmp_list)->content);
			(*tmp_list)->content = expand(tmp_str, *tmp_env);
		}
		ft_free_char(tmp_str);
		*tmp_list = list_next(tmp_list);
	}
	free_expander(tmp_env, tmp_list);
}
