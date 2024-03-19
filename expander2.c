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
			while (str[i] && str[i] != '$' && str[i] != ' '
				&& str[i] != '\"' && str[i] != '\'')
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

char	*join_expand_quoted(char *end_str, char *tmp)
{
	char	*join;

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

char	*expand(char *str, t_env *env)
{
	int		i;
	char	*end_str;
	int		start;
	char	*tmp;
	char	*expand;

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
			if (ft_strchr(tmp, '$') != 0)
			{
				expand = expand_quoted(tmp, env);
				ft_free_char(tmp);
				end_str = join_expand_quoted(end_str, expand);
			}
			else
			{
				end_str = join_expand_quoted(end_str, tmp);
				ft_free_char(tmp);
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
