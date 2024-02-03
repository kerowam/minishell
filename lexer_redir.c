#include "minishell.h"

int	get_redir_index(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			return (i);
		i++;
	}
	return (-1);
}

int	split_redirs_3(t_list *list, char *tmp_word, int i)
{
	char	*tmp_split;
	int		redir_index;
	char	redir;

	if (tmp_word[i] == '>' || tmp_word[i] == '<')
	{
		redir = tmp_word[i];
		if (tmp_word[i + 1] == redir)
		{
			if (redir == '>')
				insert_node(&list, ft_strdup(">>"));
			else
				insert_node(&list, ft_strdup("<<"));
			i += 2;
		}
		else
		{
			if (redir == '>')
				insert_node(&list, ft_strdup(">"));
			else
				insert_node(&list, ft_strdup("<"));
			i++;
		}
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


void	set_redir(t_list *list, char redir, char *tmp_word, int i)
{
	if (tmp_word[i + 1] == redir)
	{
		if (redir == '>')
			list->content = ft_strdup(">>");
		else
			list->content = ft_strdup("<<");
	}
	else
	{
		if (redir == '>')
			list->content = ft_strdup(">");
		else
			list->content = ft_strdup("<");
	}
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

int	get_redirection_nbr(char *line, int i)
{
	int		redirection_nbr;
	char	redir;

	redirection_nbr = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			redirection_nbr++;
			redir = line[i];
			if (line[i + 1] == redir)
				i++;
		}
		i++;
	}
	return (redirection_nbr);
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

	tmp = (t_list **)malloc(sizeof(t_list *));
	*tmp = *list;
	while (*tmp)
	{
		tmp = handle_quotes(tmp);
		tmp = handle_redirections(tmp, 0);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			break ;
	}
	free (tmp);
	return (list);
}