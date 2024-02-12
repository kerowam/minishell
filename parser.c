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

void	parse(t_process *process, t_list **words_splited)
{
	char	*tmp_word;
	t_list	**tmp;
	int		file;

	tmp = (t_list **)malloc(sizeof(t_list *));
	*tmp = *words_splited;
	init_process(process);
	while (*tmp)
	{
		tmp_word = (*tmp)->content;
		if (ft_strncmp(tmp_word, "<", 2) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				perror ("minishell: syntax error near unexpected token `newline'\n");
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = (*tmp)->content;
			//Comprobar si existe el archivo.
			if (access(tmp_word, F_OK) == -1)
			{
				perror("minishell: No such file or directory\n");
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			else if (access(tmp_word, R_OK) == -1) //Comprobación de permisos. Aquí o en el executor?
			{
				perror("minishell: Permission denied\n");
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			process->infile = ft_strdup(tmp_word);
		}
		else if (ft_strncmp(tmp_word, ">", 2) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				perror ("minishell: syntax error near unexpected token `newline'\n");
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
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			if (!(process->outfile))
				process->outfile = ft_strdup(tmp_word);
			else
			{
				file = open (process->outfile, O_WRONLY, 0644);
				if (file == -1)
				{
					perror ("minishell: Error opening filen\n");
					//Liberar listas
					//Gestionar g_status
					return ;
				}
				else
				{
					write (file, "", 1); //Comprobar que funciona
					close (file);
					process->outfile = ft_strdup(tmp_word);
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
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			process->outfile_append = ft_strdup(tmp_word);
		}
		else if (ft_strncmp(tmp_word, "<<", 3) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
			{
				perror("minishell: syntax error near unexpected token `newline'\n");
				//Liberar listas
				//Gestionar g_status
				return ;
			}
			tmp_word = (*tmp)->content;
			if (!(process->here_doc))
				process->here_doc = ft_lstnew(tmp_word);
			else
				ft_lstadd_back(&process->here_doc, ft_lstnew(tmp_word));
		}
		else if (ft_strncmp(tmp_word, "|", 2) == 0)
		{
			//Comprobar que el proceso anterior está completo (tiene commando y es válido)
			process->next_process = (t_process *)malloc(sizeof(t_process));
			if (!process->next_process)
			{
				perror("Error asinging memory to t_process\n");
				return ;
			}
			init_process(process->next_process);
			process = process->next_process;
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
		else if (process->command == NULL)
			process->command = ft_strdup(tmp_word);
		else if (ft_strncmp(tmp_word, "-", 1) == 0)
		{
			if (!(process->flags))
				process->flags = ft_lstnew(tmp_word);
			else
				ft_lstadd_back(&process->flags, ft_lstnew(tmp_word));
		}
		else
		{
			if (!(process->argv))
				process->argv = ft_lstnew(tmp_word);
			else
				ft_lstadd_back(&process->argv, ft_lstnew(tmp_word));
		}
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		else
			break ;
	}
	//Liberar listas
}
