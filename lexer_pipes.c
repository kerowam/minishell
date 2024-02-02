#include "minishell.h"

int	split_pipe_2(t_list *list, int i, char *tmp_split, char *tmp_word)
{
	int	pipe_index;

	pipe_index = get_pipe_index(tmp_word, i);
	if (pipe_index == 0)
	{
		list->content = ft_strdup("|");
		i++;
	}
	else
	{
		tmp_split = ft_substr(tmp_word, 0, pipe_index);
		list->content = tmp_split;
		i = pipe_index;
	}
	return (i);
}

char	*get_tmp_split(int pipe_index, char *tmp_word, int i)
{
	int		end;
	char	*tmp_split;

	if (pipe_index > 0)
		tmp_split = ft_substr(tmp_word, i, pipe_index - i);
	else
	{
		end = get_end_index(tmp_word, i);
		tmp_split = ft_substr(tmp_word, i, end);
	}
	return (tmp_split);
}

int	split_pipe_3(t_list *list, char *tmp_word, int i)
{
	char	*tmp_split;
	int		pipe_index;

	if (tmp_word[i] == '|')
	{
		insert_node(&list, ft_strdup("|"));
		i++;
	}
	else
	{
		pipe_index = get_pipe_index(tmp_word, i);
		tmp_split = get_tmp_split(pipe_index, tmp_word, i);
		insert_node(&list, tmp_split);
		i = pipe_index;
	}
	return (i);
}

t_list	*split_pipe(t_list *list, int i)
{
	char	*tmp_word;
	char	*tmp_split;

	tmp_word = list->content;
	tmp_split = NULL;
	while (tmp_word[i])
	{
		if (i == 0)
		{
			i = split_pipe_2(list, i, tmp_split, tmp_word);
		}
		else
		{
			i = split_pipe_3(list, tmp_word, i);
			list = list->next;
		}
	}
	return (list);
}

t_list	**split_pipes(t_list **list)
{
	t_list	**tmp;

	tmp = (t_list **)malloc(sizeof(t_list *));
	*tmp = *list;
	while (*tmp)
	{
		tmp = handle_quotes(tmp);
		tmp = handle_pipes(tmp, 0);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			break ;
	}
	*tmp = *list;
	return (tmp);
}
