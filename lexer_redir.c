#include "minishell.h"

int	split_redirs_3(char *tmp_word, int i, t_list **redir_splited)
{
	char	*tmp_split;
	int		redir_index;
	char	redir;

	if (tmp_word[i] == '>' || tmp_word[i] == '<')
	{
		redir = tmp_word[i];
		i = insert_redirs(redir, redir_splited, tmp_word, i);
	}
	else
	{
		redir_index = get_redir_index(tmp_word, i);
		tmp_split = get_tmp_split(redir_index, tmp_word, i);
		ft_lstadd_back(redir_splited, ft_lstnew(tmp_split));
		//insert_node(&list, tmp_split);
		i = redir_index;
	}
	return (i);
}

int	split_redirs_2(int i, char *tmp_word, t_list **redir_splited)
{
	int		redir_index;
	char	redir;
	char	*tmp_split;

	redir_index = get_redir_index(tmp_word, i);
	if (redir_index == 0)
	{
		redir = tmp_word[i];
		set_redir(redir_splited, redir, tmp_word, i);
		if (tmp_word[i + 1] == redir)
			i += 2;
		else
			i++;
	}
	else
	{
		tmp_split = ft_substr(tmp_word, 0, redir_index);
		printf("17.1.tmp_split pointer = %p\n", tmp_split);
		ft_lstadd_back(redir_splited, ft_lstnew(tmp_split));
		//list->content = ft_strdup(tmp_split);
		free(tmp_split); // added
		i = redir_index;
	}
	return (i);
}

void	split_redirection(t_list *list, int i, t_list **redir_splited)
{
	char	*tmp_word;
	//char	*tmp_split;

	tmp_word = ft_strdup(list->content);
	//tmp_split = NULL;
	while (tmp_word[i])
	{
		if (i == 0)
			i = split_redirs_2(i, tmp_word, redir_splited);
		else
		{
			i = split_redirs_3(tmp_word, i, redir_splited);
			//*list = (*list)->next;
		}
	}
	free(tmp_word);
	return ;
}

void	handle_redirections(t_list **list, int i, t_list **redir_splited)
{
	char	*tmp_word;
	int		len;
	int		n_redirections;

	//tmp_word = NULL;
	tmp_word = ft_strdup((*list)->content);
	len = ft_strlen(tmp_word);
	n_redirections = get_redirection_nbr(tmp_word, i);
	if (len > 0 && n_redirections > 0)
	{
		split_redirection(*list, i, redir_splited);
	}
	else if (len > 0)
		ft_lstadd_back(redir_splited, ft_lstnew(tmp_word));
	free(tmp_word);
	return ;
}

t_list	**split_redirections(t_list **list, t_list **redir_splited)
{
	t_list	**tmp;

	tmp = (t_list **)malloc(sizeof(t_list *));
	init_list(redir_splited);
	*tmp = *list;
	printf("18.split_redirections tmp pointer = %p\n", tmp);
	if (!tmp)
	{
		put_error(MEMPROBLEM, 1);
		return (NULL);
	}
	*tmp = *list;
	while (*tmp != NULL)
	{
		handle_redirections(tmp, 0, redir_splited);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			*tmp = NULL;
	}
	//tmp = list;
	//free (tmp);
	return (redir_splited);
}
