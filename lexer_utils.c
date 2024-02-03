#include "minishell.h"

int	get_pipe_nbr(char *line, int i)
{
	int		pipe_nbr;

	pipe_nbr = 0;
	while (line[i])
	{
		if (line[i] == '|')
			pipe_nbr++;
		i++;
	}
	return (pipe_nbr);
}

int get_pipe_index(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}

int	get_end_index(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i])
	{
		j++;
		i++;
	}
	return (j);
}

void	insert_node(t_list **list, char *content)
{
	t_list	*new_node;
	t_list	*tmp;

	new_node = ft_lstnew(content);
	if (!new_node)
		return ;
	tmp = (*list)->next;
	(*list)->next = new_node;
	new_node->next = tmp;
}

char *get_tmp_split(int target_index, char *tmp_word, int i)
{
	int end;
	char *tmp_split;

	if (target_index > 0)
		tmp_split = ft_substr(tmp_word, i, target_index - i);
	else
	{
		end = get_end_index(tmp_word, i);
		tmp_split = ft_substr(tmp_word, i, end);
	}
	return (tmp_split);
}
