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
	printf("19.0.new_node pointer = %p\n", new_node);
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
	{
		tmp_split = ft_substr(tmp_word, i, target_index - i); ////******
		if (tmp_split == NULL)
			return (free(tmp_split), NULL);
	}
	else
	{
		end = get_end_index(tmp_word, i);
		tmp_split = ft_substr(tmp_word, i, end); ////********
		if (tmp_split == NULL)
			return (free(tmp_split), NULL);
	}
	printf("19.get_tmp_split tmp_split pointer = %p\n", tmp_split);
	return (tmp_split);
}

int	search_end_quoted_string(char q, char *line, int i)
{
	while (line[i] != q)
		i++;
	i++;
	return (i);
}
