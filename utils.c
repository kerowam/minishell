
#include "minishell.h"

void	free_str_array(char **str_array)
{
	size_t	i;

	if (str_array == NULL)
		return ;
	if (str_array)
	{
		i = 0;
		while (str_array[i] != NULL)
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
	}
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
