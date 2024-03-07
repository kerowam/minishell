#include "minishell.h"

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
		if (ft_strncmp(key, name, ft_strlen(name)) == 0)
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
	value = ft_strdup("");
	return (value);
}

char	*expand_value(char *str, int i, t_env *env, char *end_str)
{
	char	*value;
	char	*tmp;

	tmp = set_key(str, i);
	value = get_expanded_value(env, tmp);
	if (!end_str)
		end_str = ft_strdup(value);
	else
		end_str = ft_strjoin(end_str, value);
	free(tmp);
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
	return (end_str);
}

void	expander(t_env *env, t_list **line_splited)
{
	t_env	**tmp_env;
	t_list	**tmp_list;
	char	*tmp_str;

	tmp_env = (t_env **)ft_calloc(0, sizeof(t_env *));
	if (tmp_env == NULL)
		return ;
	*tmp_env = env;
	tmp_list = (t_list **)ft_calloc(0, sizeof(t_list *));
	*tmp_list = *line_splited;
	while (*tmp_list != NULL)
	{
		tmp_str = ft_strdup((*tmp_list)->content);
		if (ft_strchr(tmp_str, '$') != 0)
			(*tmp_list)->content = expand(tmp_str, *tmp_env);
		if ((*tmp_list)->next)
		{
			*tmp_list = (*tmp_list)->next;
			ft_free_char(tmp_str);
		}
		else
			*tmp_list = NULL;
	}
	free_expander(tmp_env, tmp_list, tmp_str);
}
