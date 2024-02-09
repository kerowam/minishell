#include "minishell.h"

void	init_process(t_process **process)
{
	*process = (t_process *)malloc(sizeof(t_process));
	if (!*process)
	{
		perror("Error asinging memory to t_process\n");
		return ;
	}
	(*process)->next_process = NULL;
	(*process)->command = NULL;
	(*process)->flags = NULL;
	(*process)->argv = NULL;
	(*process)->pid = 0;
	(*process)->infile = NULL;
	(*process)->inf = 0;
	(*process)->outfile = NULL;
	(*process)->outf = 1;
	(*process)->outfile_append = NULL;
	(*process)->here_doc = NULL;
	(*process)->stderr = 2;
	(*process)->completed = 0;
	(*process)->stopped = 0;
	(*process)->status = 0;
}

void	parse(t_process **process, t_list **words_splited)
{
	char	*tmp_word;
	t_list	**tmp;

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
				perror("minishell: syntax error near unexpected token `newline'\n");
			tmp_word = (*tmp)->content;
			//Comprobar si existe el archivo.
			if (!((*process)->infile))
				(*process)->infile = ft_strdup(tmp_word);
			else
				//Comprobar si existe el archivo:
				// si no existe -> Error
				// si existe -> Sustituir infile
		}
		else if (ft_strncmp(tmp_word, ">", 2) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
				perror ("minishell: syntax error near unexpected token `newline'\n");
			tmp_word = (*tmp)->content;
			if (!((*process)->outfile))
				(*process)->outfile = ft_strdup(tmp_word);
			else
				//Comprobar si existe el archivo:
				// si no existe -> Crear archivo
				// si existe -> Sustituir outfile
			(*process)->outfile = ft_strdup(tmp_word);
		}
		else if (ft_strncmp(tmp_word, ">>", 3) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
				perror("minishell: syntax error near unexpected token `newline'\n");
			tmp_word = (*tmp)->content;
			if (!((*process)->outfile_append))
				(*process)->outfile_append = ft_strdup(tmp_word);
			else
				//Comprobar si existe el archivo:
				// si no existe -> Crear archivo
				// si existe -> Sustituir outfile_append
		}
		else if (ft_strncmp(tmp_word, "<<", 3) == 0)
		{
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			else
				perror("minishell: syntax error near unexpected token `newline'\n");
			tmp_word = (*tmp)->content;
			if (!((*process)->here_doc))
				ft_lstnew(tmp_word);
			else
				ft_lstadd_back(&(*process)->here_doc, ft_lstnew(tmp_word));
			(*process)->here_doc = ft_strdup(tmp_word);
		}
	}
}
