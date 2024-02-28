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
			//insert_node(&list, ft_strdup(">>"));
		else
			ft_lstadd_back(list, ft_lstnew("<<"));
			//insert_node(&list, ft_strdup("<<"));
		i += 2;
	}
	else
	{
		if (redir == '>')
			ft_lstadd_back(list, ft_lstnew(">"));
			//insert_node(&list, ft_strdup(">"));
		else
			ft_lstadd_back(list, ft_lstnew("<"));
			//insert_node(&list, ft_strdup("<"));
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
			//list->content = ft_strdup(">>");
		else
			ft_lstadd_back(list, ft_lstnew("<<"));
			//list->content = ft_strdup("<<");
	}
	else
	{
		if (redir == '>')
			ft_lstadd_back(list, ft_lstnew(">"));
			//list->content = ft_strdup(">");
		else
			ft_lstadd_back(list, ft_lstnew("<"));
			//list->content = ft_strdup("<");
	}
}

int	get_redirection_nbr(char *line, int i)
{
	int		redirection_nbr;
	char	redir;

	redirection_nbr = 0;
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
