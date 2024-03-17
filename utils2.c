#include "minishell.h"

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

void	print_process(t_process *process)
{
	int	i;

	i = 0;
	while (process)
	{
		printf("process[%d]:\n", i);
		printf("command = %s\n", process->command);
		printf("argv:\n");
		print_list_splited(&process->argv);
		printf("infile = %s\n", process->infile);
		printf("outfile = %s\n", process->outfile);
		printf("outfile_append = %s\n", process->outfile_append);
		printf("here_doc:\n");
		print_list_splited(&process->here_doc);
		if (process->args)
			print_split(process->args);
		if (process->next_process)
		{
			process = process->next_process;
			i++;
		}
		else
			break ;
	}
}

char	*ft_strndup(const char *str, size_t n)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	if (str == NULL)
		return (NULL);
	len = 0;
	while (len < n && str[len] != '\0')
		len++;
	new_str = (char *)malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}

char	*obtain_env_name(char *fullenv)
{
	int	i;

	i = 0;
	if (fullenv[0] == '=' && !fullenv[1])
		return (ft_strdup("="));
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, 0, i));
}

char	*obtain_env_value(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, i + 1, ft_strlen(fullenv) - i));
}
