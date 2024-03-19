#include "minishell.h"

int	search_end_str(char *str, int i)
{
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}

int	search_end_str2(char *str, int i)
{
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

char	*expand_quoted(char *str, t_env *env)
{
	int		i;
	char	*end_str;

	i = 0;
	end_str = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			end_str = expand_value(str, i, env, end_str);
			while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
				i++;
		}
		else
		{
			end_str = join_expand3(str, i, end_str);
			i = search_end_str2(str, i);
		}
	}
	return (end_str);
}

char	*expand(char *str, t_env *env)
{
	int		i;
	char	*end_str;
	int		start;
	char	*tmp;
	char	*join;

	i = 0;
	end_str = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			start = i;
			i = search_end_quoted_string(str[i], str, i + 1);
			end_str = join_expand(str, start, end_str, i);
		}
		else if (str[i] == '\"')
		{
			start = i;
			i = search_end_quoted_string(str[i], str, i + 1);
			tmp = ft_substr(str, start, i - start);
			//end_str = join_expand(str, start, end_str, i);
			if (ft_strchr(tmp, '$') != 0)
				tmp = expand_quoted(tmp, env);
			if (!end_str)
			{
				end_str = ft_strdup(tmp);
				ft_free_char(tmp);
				return (end_str);
			}
			else
			{
				join = ft_strjoin(end_str, tmp);
				ft_free_char(end_str);
				return (ft_free_char(tmp), join);
			}
		}
		else if (str[i] == '$')
		{
			i++;
			end_str = expand_value(str, i, env, end_str);
			while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
				i++;
		}
		else
		{
			end_str = join_expand2(str, i, end_str);
			i = search_end_str(str, i);
		}
	}
	if (end_str == NULL)
		end_str = ft_strdup(str);
	return (end_str);
}

int	check_memory(t_env **tmp_env, t_list **tmp_list)
{
	if (tmp_env == NULL || tmp_list == NULL)
	{
		put_error(MEMPROBLEM, 1);
		return (1);
	}
	return (0);
}

void	expander(t_env *env, t_list **line_splited)
{
	t_env	**tmp_env;
	t_list	**tmp_list;
	char	*tmp_str;

	tmp_env = (t_env **)ft_calloc(0, sizeof(t_env *));
	tmp_list = (t_list **)ft_calloc(0, sizeof(t_list *));
	if (check_memory(tmp_env, tmp_list) == 1)
		return ;
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
		tmp_str = NULL;
		*tmp_list = list_next(tmp_list);
	}
	free_expander(tmp_env, tmp_list);
}
