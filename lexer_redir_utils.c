#include "minishell.h"

int	get_redir_index(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = search_end_quoted_string(line[i], line, i + 1);
		else if (line[i] != '\'' && line [i] != '\"' && line[i] != '>'
			&& line[i] != '<')
			i++;
		else if (line[i] == '>' || line[i] == '<')
			return (i);
	}
	return (-1);
}

int	insert_redirs(char redir, t_list **list, char *tmp_word, int i)
{
	if (tmp_word[i + 1] == redir)
	{
		if (redir == '>')
			ft_lstadd_back(list, ft_lstnew(">>"));
		else
			ft_lstadd_back(list, ft_lstnew("<<"));
		i += 2;
	}
	else
	{
		if (redir == '>')
			ft_lstadd_back(list, ft_lstnew(">"));
		else
			ft_lstadd_back(list, ft_lstnew("<"));
		i++;
	}
	return (i);
}

void	set_redir(t_list **list, char redir, char *tmp_word, int i)
{
	if (tmp_word[i + 1] == redir)
	{
		if (redir == '>')
			ft_lstadd_back(list, ft_lstnew(">>"));
		else
			ft_lstadd_back(list, ft_lstnew("<<"));
	}
	else
	{
		if (redir == '>')
			ft_lstadd_back(list, ft_lstnew(">"));
		else
			ft_lstadd_back(list, ft_lstnew("<"));
	}
}

int	get_redirection_nbr(char *line, int i)
{
	int		redirection_nbr;
	char	redir;

	redirection_nbr = 0;
	if (line == NULL)
		return (EXIT_FAILURE);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = search_end_quoted_string(line[i], line, i + 1);
		else if (line[i] != '\'' && line [i] != '\"' && line[i] != '>'
			&& line[i] != '<')
			i++;
		else if (line[i] == '>' || line[i] == '<')
		{
			redirection_nbr++;
			redir = line[i];
			i++;
			if (line[i] == redir)
				i++;
		}
	}
	return (redirection_nbr);
}

void	add_node(t_list **list, char *tmp_word, char *tmp_split)
{
	if ((*list)->content == NULL)
		(*list)->content = ft_strdup(tmp_word);
	else
		ft_lstadd_back(list, ft_lstnew(tmp_split));
}
