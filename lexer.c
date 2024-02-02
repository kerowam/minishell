#include "minishell.h"

static int	search_end_quoted_string(char q, char *line, int i)
{
	while (line[i] != q)
		i++;
	i++;
	return (i);
}

static int	len_split(char *line, int i)
{
	int		start;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			start = i;
			if (line[i] == '\'')
				i = search_end_quoted_string('\'', line, i + 1);
			else
				i = search_end_quoted_string('\"', line, i + 1);
			return (i - start);
		}
		else if (line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
		{
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '\''
				&& line[i] != '\"')
				i++;
			return (i - start);
		}
	}
	return (0);
}

t_list	**create_line_splited(char *line, t_list **list)
{
	char	*tmp_word;
	int		i;
	int		start;
	t_list	**tmp;

	tmp = list;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] != ' ' && line[i])
		{
			start = i;
			i = len_split(line, i) + start;
			tmp_word = (char *)malloc(sizeof(char) * (i - start + 1));
			tmp_word = ft_substr(line, start, i - start);
			ft_lstadd_back(tmp, ft_lstnew(tmp_word));
		}
	}
	tmp = list;
	return (tmp);
}
