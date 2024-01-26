#include "minishell.h"

static int	search_end_quoted_string(char q, char *line, int i)
{
	while (line[i] != q)
		i++;
	i++;
	return (i);
}



/*static*/ int	word_counter(char	*line)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == Q || line[i] == D_Q)
		{
			count++;
			if (line[i] == Q)
				i = search_end_quoted_string(Q, line, i + 1);
			else
				i = search_end_quoted_string(D_Q, line, i + 1);
		}
		else if (line[i] == ' ')
			i++;
		else if (line[i] != ' ' && line[i] != Q && line[i] != D_Q)
		{
			count++;
			while (line[i] && line[i] != ' ' && line[i] != Q && line[i] != D_Q)
				i++;
		}
	}
	return (count);
}

char	**split_line(char *line)
{

}

char	**create_line_splited(char *line)
{
	char	**first_split;
	int		n_words;
	int		i;
	int		start;

	n_words = word_counter(line);
	if (n_words == 0)
		return (NULL);
	first_split = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!first_split)
		return (NULL);
	
}
