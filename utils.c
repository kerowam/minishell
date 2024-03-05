#include "minishell.h"

void	env_add_back(t_env **root, t_env *new)
{
	t_env	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

// Para comprobar lo que se aloja en la linea dividida
void	print_split(char **line_splited)
{
	int	i;

	i = 0;
	while (line_splited[i] != NULL)
		i++;
}
