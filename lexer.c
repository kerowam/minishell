#include "minishell.h"

static int	len_split(char *line, int i)
{

	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = search_end_quoted_string(line[i], line, i + 1);
		else
			i++;
	}
	return (i);
}

void	create_line_splited(char *line, t_list **list)
{
	char	*tmp_word;
	int		i;
	int		start;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] != ' ' && line[i])
		{
			start = i;
			i = len_split(line, i);
			tmp_word = (char *)malloc(sizeof(char) * (i - start + 1));
			tmp_word = ft_substr(line, start, i - start);
			ft_lstadd_back(list, ft_lstnew(tmp_word));
		}
	}
}

char	*rm_unprint_quotes(char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
		str = ft_substr(str, 1, ft_strlen(str) - 2);
	return (str);
}

void	clean_str_quot(char *str, t_list **list)
{
	int		i;
	int		start;
	char	*end_str;
	char	*tmp_str;

	i = 0;
	end_str = NULL;
	tmp_str = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i + 1;
			i = search_end_quoted_string(str[i], str, i + 1);
			tmp_str = ft_substr(str, start, i - start - 1);
			if (!end_str)
				end_str = ft_strdup(tmp_str);
			else
				end_str = ft_strjoin(end_str, tmp_str);
			free(tmp_str);
			i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			tmp_str = ft_substr(str, start, i - start);
			if (!end_str)
				end_str = ft_strdup(tmp_str);
			else
				end_str = ft_strjoin(end_str, tmp_str);
			free(tmp_str);
			i++;
		}
	}
	(*list)->content = end_str;
}

//Función de prueba. Quitar o adaptar
void	quot_cleaner(t_list **list)
{
	t_list	**tmp;
	char	*tmp_word;

	tmp = (t_list **)malloc(sizeof(t_list *));
	*tmp = *list;
	while (*tmp)
	{
		tmp_word = (*tmp)->content;
		clean_str_quot(tmp_word, tmp);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			break ;
	}
	free (tmp);
	//return (list);
}
