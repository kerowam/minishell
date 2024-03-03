#include "minishell.h"

void	init_process(t_process *process)
{
	process->next_process = NULL;
	process->command = NULL;
	process->argv = NULL;
	process->args = NULL;
	process->pid = 0;
	process->infile = NULL;
	process->in_fd = 0;
	process->outfile = NULL;
	process->outf = 1;
	process->appendf = 1;
	process->outfile_append = NULL;
	process->here_doc = NULL;
	process->stderr = 2;
	process->completed = 0;
	process->stopped = 0;
	process->status = 0;
}

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**list_to_array(t_list *list)
{
	char	**array;
	int		i;
	t_list	*tmp;

	i = ft_lstsize(list);
	tmp = NULL;
	array = (char **)malloc(sizeof(char *) * (i + 1));
	printf("25.array pointer = %p\n", array);
	if (!array)
	{
		put_error(MEMPROBLEM, 1); //exit status 1???
		return (NULL);
	}
	i = 0;
	tmp = list;
	while (tmp)
	{
		array[i] = ft_strdup(tmp->content);
		printf("26.array[%d] pointer = %p\n", i, array[i]);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

int	check_redir(char *tmp_word)
{
	if (ft_strncmp(tmp_word, "|", 2) == 0
		|| ft_strncmp(tmp_word, ">", 2) == 0
		|| ft_strncmp(tmp_word, ">>", 3) == 0
		|| ft_strncmp(tmp_word, "<<", 3) == 0
		|| ft_strncmp(tmp_word, "<", 2) == 0)
	{
		put_error(UNEXPECTEDTOKEN, 258);
		//free (tmp);
		//free_list (words_splited);
		//Liberar listas
		//Gestionar g_status
		return (1);
	}
	return (0);
}
