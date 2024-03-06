#include "minishell.h"

int	get_len_word(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] != ' ' && str[i])
	{
		i++;
		len++;
	}
	return (len);
}

char	*set_key(char *str, int i)
{
	size_t	len;
	char	*tmp;

	len = get_len_word(str, i);
	tmp = ft_substr(str, i, len);
	if (tmp == NULL)
		return (NULL);
	//printf("6.tmp pointer = %p\n", tmp);
	return (tmp);
}
