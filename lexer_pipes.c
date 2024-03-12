#include "minishell.h"

int	split_pipe_2(int i, char *tmp_word, t_list **pipes_splited)
{
	int		pipe_index;
	char	*tmp_split;

	tmp_split = NULL;
	pipe_index = get_pipe_index(tmp_word, i);
	if (pipe_index == 0)
	{
		ft_lstadd_back(pipes_splited, ft_lstnew("|"));
		i++;
	}
	else
	{
		tmp_split = ft_substr(tmp_word, 0, pipe_index);
		//printf("16.tmp_split pointer = %p\n", tmp_split);
		if ((*pipes_splited)->content == NULL)
			(*pipes_splited)->content = ft_strdup(tmp_split);
		else
			ft_lstadd_back(pipes_splited, ft_lstnew(tmp_split));
		i = pipe_index;
	}
	free(tmp_split);
	tmp_split = NULL;
	return (i);
}

int	split_pipe_3(char *tmp_word, int i, t_list **pipes_splited)
{
	char	*tmp_split;
	int		pipe_index;

	if (tmp_word[i] == '|')
	{
		tmp_split = ft_substr(tmp_word, i, 1);
		//printf("16.0.tmp_split pointer = %p\n", tmp_split);
		ft_lstadd_back(pipes_splited, ft_lstnew(tmp_split));
		i++;
	}
	else
	{
		pipe_index = get_pipe_index(tmp_word, i);
		tmp_split = get_tmp_split(pipe_index, tmp_word, i);
		//printf("16.1.tmp_split pointer= %p\n", tmp_split);
		if (tmp_split == NULL)
			return (-1);
		ft_lstadd_back(pipes_splited, ft_lstnew(tmp_split));
		i = pipe_index;
	}
	free(tmp_split);
	tmp_split = NULL;
	return (i);
}

void	split_pipe(t_list *list, int i, t_list **pipes_splited)
{
	char	*tmp_word;

	tmp_word = ft_strdup(list->content);
	//printf("16.3.split_pipe tmp_word pointer = %p\n", tmp_word);
	while (tmp_word[i] && i >= 0)
	{
		if (i == 0)
			i = split_pipe_2(i, tmp_word, pipes_splited);
		else
			i = split_pipe_3(tmp_word, i, pipes_splited);
	}
	free(tmp_word);
	tmp_word = NULL;
	return ;
}

void	handle_pipes(t_list **list, int i, t_list **pipes_splited)
{
	char	*tmp_word;
	int		len;
	int		n_pipes;

	tmp_word = ft_strdup((*list)->content);
	//printf("16.4.handle_pipes tmp_word pointer = %p\n", tmp_word);
	len = ft_strlen(tmp_word);
	n_pipes = get_pipe_nbr(tmp_word, i);
	if (len > 0 && n_pipes > 0)
		split_pipe(*list, i, pipes_splited);
	else if (len > 0)
	{
		if ((*pipes_splited)->content == NULL)
			(*pipes_splited)->content = ft_strdup(tmp_word);
		else
			ft_lstadd_back(pipes_splited, ft_lstnew(tmp_word));
	}
	//printf("16.5.handle_pipes pipes_splited pointer = %p\n", *pipes_splited);
	free(tmp_word);
	tmp_word = NULL;
	return ;

}

void	split_pipes(t_list **list, t_list **pipes_splited)
{
	t_list	**tmp;

	tmp = (t_list **)ft_calloc(0, sizeof(t_list *));
	*tmp = *list;
	//printf("17.split_pipes tmp pointer = %p\n", tmp);
	while (*tmp != NULL)
	{
		handle_pipes(tmp, 0, pipes_splited);
		if ((*tmp)->next != NULL && (*tmp)->next->content != NULL)
			*tmp = (*tmp)->next;
		else
			*tmp = NULL;
	}
	free(tmp);
	tmp = NULL;
	return ;
}
