#include "minishell.h"

char	*add_quot_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;

	tmp_str = ft_substr(str, start, i - start - 1);
	if (!end_str)
		end_str = ft_strdup(tmp_str);
	else
		end_str = ft_strjoin(end_str, tmp_str);
	printf("32.add_quot_substr end_str pointer = %p\n", end_str);
	free(tmp_str);
	return (end_str);
}

char	*add_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;

	tmp_str = ft_substr(str, start, i - start);
	if (!end_str)
		end_str = ft_strdup(tmp_str);
	else
		end_str = ft_strjoin(end_str, tmp_str);
	printf("33.add_substr end_str pointer = %p\n", end_str);
	if (tmp_str)
		free(tmp_str);
	return (end_str);
}

void	clean_str_quot(char *str, t_list **list)
{
	int		i;
	int		start;
	char	*end_str;

	i = 0;
	end_str = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i + 1;
			i = search_end_quoted_string(str[i], str, i + 1);
			end_str = add_quot_substr(start, i, str, end_str);
			i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			end_str = add_substr(start, i, str, end_str);
			i++;
		}
		printf("34.clean_str_quot end_str pointer = %p\n", end_str);
	}
	(*list)->content = ft_strdup (end_str);
	free (end_str);
}

void	quot_cleaner(t_list **list)
{
	t_list	**tmp;
	char	*tmp_word;

	tmp = (t_list **)malloc(sizeof(t_list *)); // Comprobar si es necesario malloc
	//printf("quot_cleaner tmp pointer = %p\n", tmp);
	*tmp = *list;
	printf("35.quot_cleaner *tmp pointer = %p\n", *tmp);
	while (*tmp)
	{
		tmp_word = ft_strdup((*tmp)->content);
		clean_str_quot(tmp_word, tmp);
		free (tmp_word);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			break ;
	}
	//free (*tmp);
	free (tmp);
}
