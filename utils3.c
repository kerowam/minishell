#include "minishell.h"

void	free_elements(char *temp, char *full_path)
{
	free(temp);
	free(full_path);
}
