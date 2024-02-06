#include "minishell.h"

int	split_redirs_3(t_list *list, char *tmp_word, int i)
{
	char	*tmp_split;
	int		redir_index;
	char	redir;

	if (tmp_word[i] == '>' || tmp_word[i] == '<')
	{
		redir = tmp_word[i];
		i = insert_redirs(redir, list, tmp_word, i);
	}
	else
	{
		redir_index = get_redir_index(tmp_word, i);
		tmp_split = get_tmp_split(redir_index, tmp_word, i);
		insert_node(&list, tmp_split);
		i = redir_index;
	}
	return (i);
}

int	split_redirs_2(t_list *list, int i, char *tmp_split, char *tmp_word)
{
	int		redir_index;
	char	redir;

	redir_index = get_redir_index(tmp_word, i);
	if (redir_index == 0)
	{
		redir = tmp_word[i];
		set_redir(list, redir, tmp_word, i);
		if (tmp_word[i + 1] == redir)
			i += 2;
		else
			i++;
	}
	else
	{
		tmp_split = ft_substr(tmp_word, 0, redir_index);
		list->content = tmp_split;
		i = redir_index;
	}
	return (i);
}

t_list	*split_redirection(t_list *list, int i)
{
	char	*tmp_word;
	char	*tmp_split;

	tmp_word = list->content;
	tmp_split = NULL;
	while (tmp_word[i])
	{
		if (i == 0)
			i = split_redirs_2(list, i, tmp_split, tmp_word);
		else
		{
			i = split_redirs_3(list, tmp_word, i);
			list = list->next;
		}
	}
	return (list);
}

t_list	**handle_redirections(t_list **list, int i)
{
	char	*tmp_word;
	int		len;
	int		n_redirections;

	tmp_word = (*list)->content;
	len = ft_strlen(tmp_word);
	n_redirections = get_redirection_nbr(tmp_word, i);
	if (len > 0 && n_redirections > 0)
	{
		*list = split_redirection(*list, i);
	}
	return (list);
}

t_list	**split_redirections(t_list **list)
{
	t_list	**tmp;
	char	*tmp_word;

	tmp = (t_list **)malloc(sizeof(t_list *));
	*tmp = *list;
	while (*tmp)
	{
		tmp_word = (*tmp)->content;

		if (tmp_word[0] != '\'' && tmp_word[0] != '\"')
			tmp = handle_redirections(tmp, 0);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			break ;
	}
	free (tmp);
	return (list);
}
