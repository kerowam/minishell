#include "minishell.h"

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

char	*get_tmp_split(int target_index, char *tmp_word, int i)
{
	int		end;
	char	*tmp_split;

	if (target_index > 0)
		tmp_split = ft_substr(tmp_word, i, target_index - i);
	else
	{
		end = get_end_index(tmp_word, i);
		tmp_split = ft_substr(tmp_word, i, end);
	}
	return (tmp_split);
}

t_list	**handle_quotes(t_list **list)
{
	char	*tmp_word;

	tmp_word = (*list)->content;
	if (tmp_word[0] == '\'' || tmp_word[0] == '\"')
	{
		if ((*list)->next)
			*list = (*list)->next;
	}
	return (list);
}
