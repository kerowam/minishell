#include "minishell.h"

char	*add_quot_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;

	tmp_str = ft_substr(str, start, i - start - 1);
	printf("32.0. add_quot_substr tmp_str pointer = %p\n", tmp_str);
	if (!end_str)
		end_str = ft_strdup(tmp_str);
	else
		end_str = ft_strjoin(end_str, tmp_str);
	printf("32.add_quot_substr end_str pointer = %p\n", end_str);
	free(tmp_str);
	tmp_str = NULL;
	return (end_str);
}

char	*add_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;

	tmp_str = ft_substr(str, start, i - start);
	printf("33.0.add_substr tmp_str pointer = %p\n", tmp_str);
	if (!tmp_str)
	{
		printf("Error: add_substr ft_substr failed\n");
		return (NULL);
	}
	if (!end_str)
		end_str = ft_strdup(tmp_str);
	else
		end_str = ft_strjoin(end_str, tmp_str);
	printf("33.add_substr end_str pointer = %p\n", end_str); ////********
	if (tmp_str)
		free(tmp_str);
	tmp_str = NULL;
	return (end_str);
}

void	clean_str_quot(char *str, t_list **list)
{
	int		i;
	int		start;
	char	*end_str;

	i = 0;
	end_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i + 1;
			i = search_end_quoted_string(str[i], str, i + 1);
			end_str = add_quot_substr(start, i, str, end_str);
			printf("33.1.clean_str_quot end_str pointer = %p\n", end_str);
			i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			end_str = add_substr(start, i, str, end_str);
			printf("34.clean_str_quot end_str pointer = %p\n", end_str);
			if (!end_str)
			{
				printf("Error: clean_str_quot add_substr failed\n");
				free (end_str);
				end_str = NULL;
				break ;
			}
		}
		printf("34.0.clean_str_quot end_str pointer = %p\n", end_str);
	}
	if (end_str)
	{
		if ((*list)->content)
		{
			free((*list)->content);
			(*list)->content = NULL;
		}
		(*list)->content = ft_strdup(end_str);
		printf("34.1.clean_str_quot (*list)->content = %s\n", (*list)->content);
		printf("34.2.clean_str_quot (*list)->content pointer = %p\n", (*list)->content);
		printf("34.3.clean_str_quot end_str pointer = %p\n", end_str);
		free (end_str);
		printf("34.3.1.clean_str_quot end_str pointer = %s\n", end_str);
		end_str = NULL;
		printf("34.4.clean_str_quot end_str pointer = %p\n", end_str);
	} else
		return ;
}

void	quot_cleaner(t_list **list)
{
	t_list	**tmp;
	char	*tmp_word;

	tmp = (t_list **)ft_calloc(0, sizeof(t_list *)); // Comprobar si es necesario malloc
	printf("35.0.quot_cleaner tmp pointer = %p\n", *tmp);
	if (!tmp)
	{
		printf("Error: quot_cleaner ft_calloc failed\n");
		return ;
	}
	*tmp = *list;
	printf("35.quot_cleaner *tmp pointer = %p\n", *tmp);
	while (*tmp != NULL)
	{
		tmp_word = ft_strdup((*tmp)->content);
		if (tmp_word != NULL)
		{
			clean_str_quot(tmp_word, tmp);
			free (tmp_word);
			tmp_word = NULL;
		}
		if ((*tmp)->next != NULL)
			*tmp = (*tmp)->next;
		else
			*tmp = NULL;
	}
	free (tmp);
	tmp = NULL;
}
