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
