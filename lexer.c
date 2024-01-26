#include "minishell.h"

static int	search_end_quoted_string(char q, char *line, int i)
{
	while (line[i] != q)
		i++;
	return (i);
}



static int	word_counter(char	*line)
{
	int		count;
	int		i;
	char	q;
	char	d_q;

	count = 0;
	i = 0;
	q = '\'';
	d_q = '\"';
	while (line[i])
	{
		if (line[i] == q || line[i] == d_q)
		{
			count++;
			i++;
			if (line[i] == q)
				i = search_end_quoted_string(q, line, i);
			else
				i = search_end_quoted_string(d_q, line, i);
			i++;
		}
		else if (line[i] == ' ')
			i++;
		else if (line[i] != ' ' && line[i] != q && line[i] != d_q)
		{
			count++;
			while (line[i] && line[i] != ' ' && line[i] != q && line[i] != d_q)
			i++;
		}
	}
	return (count);
}

/*char	**line_split(char *line)
{

}*/
