
#include "minishell.h"

void	free_temp(char **temp)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			free(temp[i]);
			i++;
		}
		free(temp);
	}
}

void	free_echo(char **str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	env_add_back(t_env **root, t_env *new)
{
	t_env	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = next;
	}
	*list = NULL;
}

// Para comprobar lo que se aloja en la linea dividida
void	print_split(char **line_splited)
{
	int	i;

	i = 0;
	while (line_splited[i] != NULL)
	{
		printf("line_splited[%d] = %s\n", i, line_splited[i]);
		i++;
	}
}

void	print_list_splited(t_list **list)
{
	t_list	*tmp;
	int		i;

	tmp = *list;
	i = 0;
	while (tmp)
	{
		printf("list[%d] = %s\n", i, tmp->content);
		tmp = tmp->next;
		i++;
	}
}

void	print_process(t_process *process)
{
	int	i;

	i = 0;
	while (process)
	{
		printf("process[%d]:\n", i);
		printf("command = %s\n", process->command);
		printf("flags:\n");
		print_list_splited(&process->flags);
		printf("argv:\n");
		print_list_splited(&process->argv);
		printf("infile = %s\n", process->infile);
		printf("outfile = %s\n", process->outfile);
		printf("outfile_append = %s\n", process->outfile_append);
		printf("here_doc:\n");
		print_list_splited(&process->here_doc);
		if (process->next_process)
		{
			process = process->next_process;
			i++;
		}
		else
			break ;
	}
}
