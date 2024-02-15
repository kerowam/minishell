#include "minishell.h"

void	init_process(t_process *process)
{
	/*process = (struct t_process *)malloc(sizeof(t_process));
	if (!process)
	{
		perror("Error asinging memory to t_process\n");
		return ;
	}*/
	process->next_process = NULL;
	process->command = NULL;
	process->argv = NULL;
	process->pid = 0;
	process->infile = NULL;
	process->inf = 0;
	process->outfile = NULL;
	process->outf = 1;
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
	tmp = list;
	array = (char **)malloc(sizeof(char *) * (i + 1));
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

void	check_pipe(char *tmp_word)
{
	if (ft_strncmp(tmp_word, "|", 2) == 0)
	{
		put_error(UNEXPECTEDTOKEN, 258);
		//free (tmp);
		//free_list (words_splited);
		//Liberar listas
		//Gestionar g_status
	}
	return ;
}

void	check_infile(char *tmp_word, t_process *tmp_process)
{
	if (access(tmp_word, F_OK) == -1)
	{
		put_error(NOTFILEORDIR, 1);
		//free (tmp);
		//free_list (words_splited);
		//Liberar listas
		//Gestionar g_status
		//return ;
		//break ;
	}
	else if (access(tmp_word, R_OK) == -1) //Comprobación de permisos. Aquí o en el executor?
	{
		put_error(NOTPERMISSION, 1);
		//free (tmp);
		//free_list (words_splited);
		//Liberar listas
		//Gestionar g_status
		//return ;
		//break ;
	}
	else
		tmp_process->infile = ft_strdup(tmp_word);
}

void	check_outfile(char *tmp_word, t_process *tmp_process)
{
	int	file;
	
	if (access(tmp_word, F_OK) == -1)
	{
		file = open (tmp_word, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if (file < 0)
		{
			put_error(OPENERROR, 1); //exit status 1???
			//free (tmp);
			//free_list (words_splited);
			//Liberar listas
			//Gestionar g_status
			//return ;
			//break ;
		}
		else
			close (file);
	}
	else if (access(tmp_word, W_OK) == -1)
	{
		put_error(NOTPERMISSION, 1);
		//free (*tmp);
		//free_list (words_splited);
		//Liberar listas
		//Gestionar g_status
		//return ;
		//break ;
	}
	if (!(tmp_process->outfile))
		tmp_process->outfile = ft_strdup(tmp_word);
	else
	{
		file = open (tmp_process->outfile, O_WRONLY, 0644);
		if (file == -1)
		{
			put_error(OPENERROR, 1); //exit status 1???
			//free (tmp);
			//free_list (words_splited);
			//Liberar listas
			//Gestionar g_status
			//return ;
			//break ;
		}
		else
		{
			write (file, "", 1); //Comprobar que funciona
			close (file);
			tmp_process->outfile = ft_strdup(tmp_word);
		}
	}
}

void	check_outfile_append(char *tmp_word, t_process *tmp_process)
{
	int	file;

	if (access(tmp_word, F_OK) == -1)
	{
		file = open (tmp_word, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if (file < 0)
		{
			put_error(OPENERROR, 1); //exit status 1???
			//free (tmp);
			//free_list (words_splited);
			//Liberar listas
			//Gestionar g_status
			//return ;
			//break ;
		}
		else
			close (file);
	}
	else if (access(tmp_word, W_OK) == -1)
	{
		put_error(NOTPERMISSION, 1);
		//free (tmp);
		//free_list (words_splited);
		//Liberar listas
		//Gestionar g_status
		//return ;
		//break ;
	}
	tmp_process->outfile_append = ft_strdup(tmp_word);
}

void	parse(t_process *process, t_list **words_splited)
{
	char		*tmp_word;
	t_list		**tmp;
	//int			file;
	t_process	*tmp_process;
	t_process	*next_process;

	tmp = (t_list **)malloc(sizeof(t_list *));
	*tmp = *words_splited;
	tmp_process = process;
	init_process(process);
	while (*tmp)
	{
		tmp_word = ft_strdup((*tmp)->content);
		if (ft_strncmp(tmp_word, "<", 2) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				put_error(UNEXPECTEDTOKEN, 258);
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = ft_strdup((*tmp)->content);
			if (check_redir(tmp_word) == 0)
				check_infile(tmp_word, tmp_process);
		}
		else if (ft_strncmp(tmp_word, ">", 2) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				put_error(UNEXPECTEDTOKEN, 258);
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = ft_strdup((*tmp)->content);
			if (check_redir(tmp_word) == 0)
				check_outfile(tmp_word, tmp_process);
		}
		else if (ft_strncmp(tmp_word, ">>", 3) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				put_error(UNEXPECTEDTOKEN, 258);
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = (*tmp)->content;
			if (check_redir(tmp_word) == 0)
				check_outfile_append(tmp_word, tmp_process);
		}
		else if (ft_strncmp(tmp_word, "<<", 3) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				put_error(UNEXPECTEDTOKEN, 258);
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = ft_strdup((*tmp)->content);
			if (check_redir(tmp_word) == 0)
			{
				if (!(tmp_process->here_doc))
					tmp_process->here_doc = ft_lstnew(ft_strdup(tmp_word));
				else
					ft_lstadd_back(&tmp_process->here_doc, ft_lstnew(ft_strdup(tmp_word)));
			}
		}
		else if (ft_strncmp(tmp_word, "|", 2) == 0)
		{
			//Comprobar que el proceso anterior está completo (tiene commando y es válido)
			tmp_process->args = list_to_array(process->argv);
			next_process = (t_process *)malloc(sizeof(t_process));
			if (!next_process)
			{
				put_error(MEMPROBLEM, 1); //exit status 1???
				//free (tmp);
				//free_list (words_splited);
				return ;
			}
			init_process(next_process);
			tmp_process->next_process = next_process;
			tmp_process = tmp_process->next_process;
			tmp_word = ft_strdup((*tmp)->next->content);
			check_pipe(tmp_word);
			/*if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				printf("minishell: nothing after pipe\n");
				//Implementar espera pare el resto del input
				//Liberar listas
				//Gestionar g_status
				return ;
			}*/
		}
		else if (tmp_process->command == NULL)
			tmp_process->command = ft_strdup(tmp_word);
		else
		{
			if (!(tmp_process->argv))
				tmp_process->argv = ft_lstnew(ft_strdup(tmp_word));
			else
				ft_lstadd_back(&tmp_process->argv, ft_lstnew(ft_strdup(tmp_word)));
		}
		if ((*tmp)->next)
		{
			(*tmp) = (*tmp)->next;
			//free (tmp_word);
		}
		else
		{
			//free (tmp);
			//free (tmp_word);
			tmp_process->args = list_to_array(tmp_process->argv);
			free (tmp_word);
			free (tmp);
			free_list (words_splited);
			return ;
		}
	}
	//free (tmp_process);
	//Liberar listas
}
