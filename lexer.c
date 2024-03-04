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
	*list = (t_list *)ft_calloc(0, sizeof(t_list)); ////******////
	printf("21.0.init_list list pointer = %p\n", *list);
	if (*list == NULL)
	{
		perror("Error allocating memory for list");
		//gestionar error.
		return ;
	}
	(*list)->content = NULL;
	(*list)->next = NULL;
}

void	create_line_splited(char *line, t_list **list)
{
	char	*tmp_word;
	int		i;
	int		start;

	i = 0;
	init_list(list);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] != ' ' && line[i])
		{
			start = i;
			i = len_split(line, i);
			tmp_word = ft_substr(line, start, i - start); ////********
			printf("21.create_line_splited ft_substr tmp_word pointer = %p\n", tmp_word);
			if ((*list)->content == NULL)
			{
				(*list)->content = ft_strdup(tmp_word);
				printf("21.1.create_line_splited list->content pointer = %p\n", (*list)->content);
			}
			else
				ft_lstadd_back(list, ft_lstnew(tmp_word));
			free (tmp_word);
			tmp_word = NULL;
		}
	}
}

void	lexer(t_data *shell, t_list **redir_splited)
{
	char	*line;
	t_list	**pipes_splited;
	t_list	**words_splited;

	pipes_splited = (t_list **)ft_calloc(0, sizeof(t_list *));
	printf("22.0.lexer pipes_splited pointer = %p\n", pipes_splited);
	words_splited = (t_list **)ft_calloc(0, sizeof(t_list *));
	printf("22.0.1.lexer words_splited pointer = %p\n", words_splited);
	line = (char *)ft_calloc(0, sizeof(char) * (ft_strlen(shell->line) + 1));
	line = ft_strdup(shell->line);
	printf("22.lexer line pointer = %p\n", line);
	printf("22.1 shell->line pointer = %p\n", shell->line);	
	//printf("line = %s\n", line);
	create_line_splited(line, words_splited);
	free((void *)line);
	line = NULL;
	//free (&line);
	split_pipes(words_splited, pipes_splited);
	free_list(words_splited);
	free(words_splited);                        /////CAMBIADO
	words_splited = NULL;
	split_redirections(pipes_splited, redir_splited);
	free_list(pipes_splited);
	free(pipes_splited);
	pipes_splited = NULL;
	expander(shell->env, redir_splited);
	quot_cleaner(redir_splited);
	//free(pipes_splited);
	//free(*pipes_splited);
	return ;
}
