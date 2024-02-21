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

void	init_list(t_list **list)
{
	*list = (t_list *)malloc(sizeof(t_list));
	(*list)->content = NULL;
	(*list)->next = NULL;
}

void	create_line_splited(char *line, t_list **list)
{
	char	*tmp_word;
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	//tmp = (t_list *)malloc(sizeof(t_list));
	//*list = tmp;
	init_list(list);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] != ' ' && line[i])
		{
			start = i;
			i = len_split(line, i);
			//tmp_word = (char *)malloc(sizeof(char) * (i - start + 1));
			//printf("20.create_line_splited malloc tmp_word pointer = %p\n", tmp_word);
			tmp_word = ft_substr(line, start, i - start);
			printf("21.create_line_splited ft_substr tmp_word pointer = %p\n", tmp_word);
			tmp = (*list)->content;
		if (!tmp)
			(*list)->content = ft_strdup(tmp_word);
		else
			ft_lstadd_back(list, ft_lstnew(tmp_word));
		free (tmp_word);
		//free(tmp);
		}
	}
	//free(line);
	//*list = tmp;
}

void	lexer(t_data *shell, t_list **words_splited)
{
	char	*line;

	line = (char *)malloc(sizeof(char) * (ft_strlen(shell->line) + 1));
	line = ft_strdup(shell->line);
	printf("22.lexer line pointer = %p\n", line);
	printf("22.1 shell->line pointer = %p\n", shell->line);	
	//printf("line = %s\n", line);
	create_line_splited(line, words_splited);
	free(line);
	//line = NULL;
	//free (&line);
	//split_pipes(words_splited);
	//split_redirections(words_splited);
	//expander(shell->env, words_splited);
	//quot_cleaner(words_splited);
	return ;
}
