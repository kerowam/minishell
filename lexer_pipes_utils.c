#include "minishell.h"

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

t_list	**handle_pipes(t_list **list, int i)
{
	char	*tmp_word;
	int		len;
	int		n_pipes;

	tmp_word = (*list)->content;
	len = ft_strlen(tmp_word);
	n_pipes = get_pipe_nbr(tmp_word, i);
	if (len > 0 && n_pipes > 0)
	{
		*list = split_pipe(*list, i);
	}
	return (list);
}
