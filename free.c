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
			str[i] = '\0';
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

	next = (t_list **)malloc(sizeof(t_list *));
	if (!next)
		return ;
	while (*tmp != NULL)
	{
		if ((*tmp)->next != NULL)
			*next = (*tmp)->next;
		else
			*next = NULL;
		if (*tmp != NULL)
			free(*tmp);
		*tmp = *next;
	}
	free (next);
}

void	free_list(t_list **list)
{
	t_list	**tmp;
	t_list	**next;

	tmp = list;
	while (tmp)
	{
		if ((*tmp)->next != NULL)
			next = &(*tmp)->next;
		else
			next = NULL;
		if ((*tmp)->content != NULL)
		{
			printf("freeing content: %s\n", (*tmp)->content);
			//getchar();
			free((*tmp)->content);
			//(*tmp)->content = NULL;
		}
		tmp = next;
	}
	if (list != NULL)
	{
		//tmp = list;
		free_list_p(list);
	}
	/*if (tmp)
		free(tmp);*/
	//list = NULL;
	//free(list);
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
		if (tmp->command != NULL)
		{
			free(tmp->command);
			tmp->command = NULL;
		}
		if (tmp->argv)
			free_list(&tmp->argv);
		if (tmp->infile)
			free(tmp->infile);
		tmp->infile = NULL;
		if (tmp->outfile)
			free(tmp->outfile);
		tmp->outfile = NULL;
		if (tmp->outfile_append)
			free(tmp->outfile_append);
		tmp->outfile_append = NULL;
		if (tmp->here_doc)
			free_list(&tmp->here_doc);
		if (tmp->args)
		{
			free_echo(tmp->args);
			/*if (tmp->args != NULL)
				free(tmp->args);*/
			tmp->args = NULL;
		}

		if (tmp)
			free(tmp);
		tmp = next;
	}
}
