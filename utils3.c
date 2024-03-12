#include "minishell.h"

void	free_elements(char *temp, char *full_path)
{
	free(temp);
	free(full_path);
}

t_list	*list_next(t_list **tmp_list)
{
	if ((*tmp_list)->next)
		*tmp_list = (*tmp_list)->next;
	else
		*tmp_list = NULL;
	return (*tmp_list);
}
