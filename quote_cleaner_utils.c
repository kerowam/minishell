#include "minishell.h"

char	*add_quot_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;

	tmp_str = ft_substr(str, start, i - start - 1);
	//printf("32.0. add_quot_substr tmp_str pointer = %p\n", tmp_str);
	if (!end_str)
		end_str = ft_strdup(tmp_str);
	else
		end_str = ft_strjoin(end_str, tmp_str);
	//printf("32.add_quot_substr end_str pointer = %p\n", end_str);
	free(tmp_str);
	tmp_str = NULL;
	return (end_str);
}

char	*add_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;

	tmp_str = ft_substr(str, start, i - start);
	//printf("33.0.add_substr tmp_str pointer = %p\n", tmp_str);
	if (!tmp_str)
	{
		printf("Error: add_substr ft_substr failed\n"); //Gestionar errores
		return (NULL);
	}
	if (!end_str)
		end_str = ft_strdup(tmp_str);
	else
		end_str = ft_strjoin(end_str, tmp_str);
	//printf("33.add_substr end_str pointer = %p\n", end_str);
	if (tmp_str)
		free(tmp_str);
	tmp_str = NULL;
	return (end_str);
}
