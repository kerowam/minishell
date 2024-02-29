#include "minishell.h"

void	free_temp(char **temp)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			free(temp[i]);
			i++;
		}
		free(temp);
	}
}

void	free_echo(char **str)
{
	int	i;

	i = 0;
	if (*str != NULL)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		if (str)
			free(str);
		str = NULL;
	}
}

void	free_list_p(t_list **tmp)
{
	t_list	**next;

	while (*tmp)
	{
		next = &(*tmp)->next;
		if (*tmp)
			free(*tmp);
		*tmp = *next;
	}
}

void	free_list(t_list **list)
{
	t_list	**tmp;
	t_list	**next;

	tmp = list;
	while (tmp)
	{
		if ((*tmp)->next)
			next = &(*tmp)->next;
		else
			next = NULL;
		if ((*tmp)->content)
		{
			printf("freeing content: %s\n", (*tmp)->content);
			//getchar();
			free((*tmp)->content);
		}
		tmp = next;
	}
	tmp = list;
	//free_list_p(tmp);
	/*if (tmp)
		free(tmp);*/
	*list = NULL;
}

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

void	free_process(t_process *process)
{
	t_process	*tmp;
	t_process	*next;

	tmp = process;
	while (tmp)
	{
		next = tmp->next_process;
		if (tmp->command)
			free(tmp->command);
		if (tmp->argv)
			free_list(&tmp->argv);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->outfile_append)
			free(tmp->outfile_append);
		if (tmp->here_doc)
			free_list(&tmp->here_doc);
		if (tmp->args)
			free_echo(tmp->args);
		if (tmp)
			free(tmp);
		tmp = next;
	}
}
