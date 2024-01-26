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

/*char	**line_split(char *line)
{
	char	**first_split;
	int		segments;
	int		i;
	int		start;

	segments = word_counter(line);
	first_split = (char **)malloc(sizeof(char *) * (segments + 1));

}*/
