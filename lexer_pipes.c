#include "minishell.h"

int	split_pipe_2(int i, char *tmp_word, t_list **pipes_splited)
{
	int		pipe_index;
	char	*tmp_split;

	pipe_index = get_pipe_index(tmp_word, i);
	if (pipe_index == 0)
	{
		ft_lstadd_back(pipes_splited, ft_lstnew("|"));
		//(*pipes_splited)->content = ft_strdup("|");	// Este ft_strdup dejará leaks?
		printf("15.list->content pointer = %p\n", (*pipes_splited)->content);
		i++;
	}
	else
	{
		tmp_split = ft_substr(tmp_word, 0, pipe_index);
		printf("16.tmp_split pointer = %p\n", tmp_split);
		ft_lstadd_back(pipes_splited, ft_lstnew(tmp_split));
		//(*pipes_splited)->content = ft_strdup(tmp_split);
		free(tmp_split);
		i = pipe_index;
	}
	return (i);
}

int	split_pipe_3(char *tmp_word, int i, t_list **pipes_splited)
{
	char	*tmp_split;
	int		pipe_index;

	if (tmp_word[i] == '|')
	{
		ft_lstadd_back(pipes_splited, ft_lstnew("|")); // 
		i++;
	}
	else
	{
		pipe_index = get_pipe_index(tmp_word, i);
		tmp_split = get_tmp_split(pipe_index, tmp_word, i);
		if (tmp_split == NULL)
		{
			printf("16.1. tmp_split= %s\n", tmp_split);
			return (-1);
		}
		ft_lstadd_back(pipes_splited, ft_lstnew(tmp_split));
		//insert_node(pipes_splited, tmp_split);
		i = pipe_index;
	}
	return (i);
}

void	split_pipe(t_list *list, int i, t_list **pipes_splited)
{
	char	*tmp_word;
	//char	*tmp_split;
	//int		splits;

	tmp_word = ft_strdup(list->content); //
	//tmp_split = NULL;
	//splits = 0;
	while (tmp_word[i] && i >= 0)
	{
		if (i == 0)
			i = split_pipe_2(i, tmp_word, pipes_splited);
		else
		{
			i = split_pipe_3(tmp_word, i, pipes_splited);
			//*pipes_splited = (*pipes_splited)->next;
			//splits++;
		}
	}
	free(tmp_word); //
	return ;
	//return (splits);
}

void	handle_pipes(t_list **list, int i, t_list **pipes_splited)
{
	char	*tmp_word;
	int		len;
	int		n_pipes;
	//int		splits;

	//splits = 0;
	tmp_word = ft_strdup((*list)->content); //
	len = ft_strlen(tmp_word);
	n_pipes = get_pipe_nbr(tmp_word, i);
	if (len > 0 && n_pipes > 0)
	{
		//splits = 
		split_pipe(*list, i, pipes_splited);
	}
	else if (len > 0)
		ft_lstadd_back(pipes_splited, ft_lstnew(tmp_word));
	free(tmp_word); //
	return ;
	//return (splits);
}

void	split_pipes(t_list **list, t_list **pipes_splited)
{
	t_list	**tmp;
	//int		splits;

	tmp = (t_list **)malloc(sizeof(t_list *));
	if (!tmp)
	{
		put_error(MEMPROBLEM, 1);
		return ;
	}
	init_list(pipes_splited);
	*tmp = *list;
	printf("17.split_pipes tmp pointer = %p\n", tmp);
	while (*tmp != NULL)
	{
		//splits = 
		handle_pipes(tmp, 0, pipes_splited);
		//while (splits >=  0)
		//{
			if ((*tmp)->next != NULL && (*tmp)->next->content != NULL)
				*tmp = (*tmp)->next;
			else
				*tmp = NULL;
		//	splits--;
		//}
		/*if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			*tmp = NULL;*/
			//break ;
	}
	//*tmp = *list;
	//free(tmp);
	return ;
}
