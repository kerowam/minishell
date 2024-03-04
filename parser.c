#include "minishell.h"

void	handle_redirection(t_list **tmp, t_process *tmp_process,
		char *tmp_word)
{
	t_list	*tmp_next;
	char	*tmp_word_next;

	tmp_next = (*tmp)->next;
	tmp_word_next = ft_strdup(tmp_next->content);
	printf("27.1.tmp_word_next pointer= %p\n", tmp_word_next);
	if (check_redir(tmp_word_next) == 0)
	{
		if (ft_strncmp(tmp_word, ">", 2) == 0)
			check_outfile(tmp_word_next, tmp_process);
		else if (ft_strncmp(tmp_word, ">>", 3) == 0)
			check_outfile_append(tmp_word_next, tmp_process);
		else if (ft_strncmp(tmp_word, "<<", 3) == 0)
		{
			if (!(tmp_process->here_doc))
				tmp_process->here_doc = ft_lstnew(tmp_word_next); //CAMBIADO
			else
				ft_lstadd_back(&tmp_process->here_doc,
					ft_lstnew(tmp_word_next));
		}
		else if (ft_strncmp(tmp_word, "<", 2) == 0)
			check_infile(tmp_word_next, tmp_process);
	}
	free(tmp_word_next);
	tmp_word_next = NULL;
	*tmp = tmp_next;
}

void	handle_pipe(t_process **tmp_process, char *tmp_word, t_list *tmp)
{
	t_process	*next_pr;

	next_pr = (t_process *)malloc(sizeof(t_process));
	if (!next_pr)
	{
		put_error(MEMPROBLEM, 1); //exit status 1???
		//free (tmp_word);
		return ;
	}
	printf("27.2.next_pr pointer = %p\n", next_pr);
	(*tmp_process)->args = list_to_array((*tmp_process)->argv);
	if (!(next_pr))
	{
		put_error(MEMPROBLEM, 1); //exit status 1???
		//free (tmp_word);
		return ;
	}
	init_process(next_pr);
	(*tmp_process)->next_process = next_pr;
	*tmp_process = (*tmp_process)->next_process;
	free (tmp_word);
	tmp_word = NULL;
	tmp_word = ft_strdup(tmp->next->content);
	printf("27.3.tmp_word pointer = %p\n", tmp_word);
	check_pipe(tmp_word);
}

void	handle_command(t_process **tmp_process, char *tmp_word)
{
	if ((*tmp_process)->command == NULL)
	{
		(*tmp_process)->command = ft_strdup(tmp_word);
		printf("27.4.(*tmp_process)->command pointer = %p\n", tmp_word);
	}
	else
	{
		if (!((*tmp_process)->argv))
			(*tmp_process)->argv = ft_lstnew(tmp_word);
		else
			ft_lstadd_back(&(*tmp_process)->argv,
				ft_lstnew(tmp_word));
	}
}

int	is_redir(char *tmp_word)
{
	if (ft_strncmp(tmp_word, ">", 2) == 0
		|| ft_strncmp(tmp_word, ">>", 3) == 0
		|| ft_strncmp(tmp_word, "<<", 3) == 0
		|| ft_strncmp(tmp_word, "<", 2) == 0)
		return (1);
	return (0);
}

void	parse(t_process *process, t_list **words_splited)
{
	char		*tmp_word;
	t_list		**tmp;
	t_process	**tmp_process;

	tmp_process = (t_process **)malloc(sizeof(t_process *));
	if (!tmp_process)
	{
		put_error(MEMPROBLEM, 1); //exit status 1???
		return ;
	}
	tmp = (t_list **)malloc(sizeof(t_list *));
	if (!tmp)
	{
		put_error(MEMPROBLEM, 1); //exit status 1???
		return ;
	}
	printf("27.5.tmp_process pointer = %p\n", tmp_process);
	//tmp = (t_list *)malloc(sizeof(t_list));
	*tmp = *words_splited;
	init_process(process);
	*tmp_process = process;
	while (*tmp)
	{
		tmp_word = ft_strdup((*tmp)->content);
		printf("27.6.tmp_word pointer = %p\n", tmp_word);
		if (is_redir(tmp_word) == 1)
			handle_redirection(tmp, *tmp_process, tmp_word);
		else if (ft_strncmp(tmp_word, "|", 2) == 0)
			handle_pipe(tmp_process, tmp_word, *tmp);
		else
			handle_command(tmp_process, tmp_word);
		if ((*tmp)->next != NULL)
		{
			//free(*tmp);
			*tmp = (*tmp)->next;
			if (tmp_word)
				free(tmp_word);
			/*if (tmp_process)
				free (tmp_process);*/
		}
		else
		{
			(*tmp_process)->args = list_to_array((*tmp_process)->argv);
			printf("27.7.(*tmp_process)->args pointer = %p\n", (*tmp_process)->args);
			free(tmp_word);
			tmp_word = NULL;
			free(tmp_process);
			tmp_process = NULL;
			free(tmp);
			return ;
		}
		//free(tmp_word); //
	}
}
