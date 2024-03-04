#include "minishell.h"

/*int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}*/

int	ft_strends(const char *str, const char *end)
{
	size_t	len_str;
	size_t	len_end;

	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	if (len_end > len_str)
		return (0);
	return (ft_strncmp(str + len_str - len_end, end, len_end) == 0);
}
