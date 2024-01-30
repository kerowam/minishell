#include "minishell.h"

static int	search_end_quoted_string(char q, char *line, int i)
{
	while (line[i] != q)
		i++;
	i++;
	return (i);
}



/*static int	word_counter(char	*line)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			count++;
			if (line[i] == '\'')
				i = search_end_quoted_string('\'', line, i + 1);
			else
				i = search_end_quoted_string('\"', line, i + 1);
		}
		else if (line[i] == ' ')
			i++;
		else if (line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
		{
			count++;
			while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
				i++;
		}
	}
	return (count);
}*/

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
			while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
				i++;
			return (i - start);
		}
	}
	return (0);
}

t_list	**create_line_splited(char *line, t_list **list)
{
	char	*tmp_word;
	//int		n_words;
	int		i;
	//int		j;
	int		start;
	t_list	**tmp;

	tmp = list;
	/*n_words = word_counter(line);
	if (n_words == 0)
		return (NULL);
	first_split = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!first_split)
		return (NULL);*/
	i = 0;
	//j = 0;
	while (line[i]/* && j < n_words*/)
	{
		if (line[i] == ' ')
			i++;
		if (line[i] != ' ' && line[i])
		{
			start = i;
			i = len_split(line, i) + start;
			tmp_word = ft_substr(line, start, i - start);
			ft_lstadd_back(tmp, ft_lstnew(tmp_word));
		}
		//j++;
		if (line[i] != '\0')
			i++;
	}
	//first_split[j] = NULL;
	tmp = list;
	//free (tmp);
	free (tmp_word);
	return (tmp);
}
