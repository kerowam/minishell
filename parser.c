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
	process->flags = NULL;
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
		perror("Error asinging memory to array\n");
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

void	parse(t_process *process, t_list **words_splited)
{
	char		*tmp_word;
	t_list		**tmp;
	int			file;
	t_process	*tmp_process;

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
				perror ("minishell: syntax error near unexpected token `newline'\n");
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = (*tmp)->content;
			//Comprobar si existe el archivo.
			if (access(tmp_word, F_OK) == -1)
			{
				perror("minishell: No such file or directory\n");
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			else if (access(tmp_word, R_OK) == -1) //Comprobación de permisos. Aquí o en el executor?
			{
				perror("minishell: Permission denied\n");
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_process->infile = ft_strdup(tmp_word);
		}
		else if (ft_strncmp(tmp_word, ">", 2) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				perror ("minishell: syntax error near unexpected token `newline'\n");
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = (*tmp)->content;
			if (access(tmp_word, F_OK) == -1)
			{
				file = open (tmp_word, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
				if (file < 0)
				{
					perror("Error opening file");
					//free (tmp);
					//free_list (words_splited);
					//Liberar listas
					//Gestionar g_status
					return ;
				}
				else
					close (file);
			}
			else if (access(tmp_word, W_OK) == -1)
			{
				perror("minishell: Permission denied\n");
				//free (*tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			if (!(tmp_process->outfile))
				tmp_process->outfile = ft_strdup(tmp_word);
			else
			{
				file = open (process->outfile, O_WRONLY, 0644);
				if (file == -1)
				{
					perror ("minishell: Error opening filen\n");
					//free (tmp);
					//free_list (words_splited);
					//Liberar listas
					//Gestionar g_status
					return ;
				}
				else
				{
					write (file, "", 1); //Comprobar que funciona
					close (file);
					tmp_process->outfile = ft_strdup(tmp_word);
				}
			}
		}
		else if (ft_strncmp(tmp_word, ">>", 3) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				perror("minishell: syntax error near unexpected token `newline'\n");
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = (*tmp)->content;
			if (access(tmp_word, F_OK) == -1)
			{
				file = open (tmp_word, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
				if (file < 0)
				{
					perror("Error opening file");
					//free (tmp);
					//free_list (words_splited);
					//Liberar listas
					//Gestionar g_status
					return ;
				}
				else
					close (file);
			}
			else if (access(tmp_word, W_OK) == -1)
			{
				perror("minishell: Permission denied\n");
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_process->outfile_append = ft_strdup(tmp_word);
		}
		else if (ft_strncmp(tmp_word, "<<", 3) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				perror("minishell: syntax error near unexpected token `newline'\n");
				//free (tmp);
				//free_list (words_splited);
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = (*tmp)->content;
			if (!(process->here_doc))
				tmp_process->here_doc = ft_lstnew(ft_strdup(tmp_word));
			else
				ft_lstadd_back(&process->here_doc, ft_lstnew(ft_strdup(tmp_word)));
		}
		else if (ft_strncmp(tmp_word, "|", 2) == 0)
		{
			//Comprobar que el proceso anterior está completo (tiene commando y es válido)
			tmp_process->next_process = (t_process *)malloc(sizeof(t_process));
			if (!tmp_process->next_process)
			{
				perror("Error asinging memory to t_process\n");
				//free (tmp);
				//free_list (words_splited);
				return ;
			}
			init_process(tmp_process->next_process);
			tmp_process = tmp_process->next_process;
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
			if (!(process->argv))
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
			free_list (words_splited);
			break ;
		}
	}
	process->args = list_to_array(process->argv);
	free (tmp);
	free (tmp_word);
	free (tmp_process);
	//Liberar listas
}
