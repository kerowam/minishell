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
			temp[i] = NULL;
			i++;
		}
		free(temp);
		temp = NULL;
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
		{
			free(*tmp);
			*tmp = NULL;
		}
		*tmp = *next;
	}
	free (next);
	next = NULL;
}

void	free_list(t_list **list)
{
	//t_list	**tmp;
	t_list	**next;

	next = (t_list **)malloc(sizeof(t_list *));
	//tmp = (t_list **)malloc(sizeof(t_list *));
	//*tmp = *list;
	while (*list != NULL)
	{
		if ((*list)->next != NULL)
			*next = (*list)->next;
		else
			*next = NULL;
		if ((*list)->content != NULL)
		{
			printf("freeing content: %s\n", (*list)->content);
			//getchar();
			free((*list)->content);
			(*list)->content = NULL;
			/*if ((*tmp)->next != NULL)
			{
				free((*tmp)->next);
				(*tmp)->next = NULL;
			}*/
		}
		free(*list);
		*list = *next;
	}
	if (list != NULL)
	{
		//tmp = list;
		free_list_p(list);
	}
	//free (tmp);
	//tmp = NULL;
	free (next);
	next = NULL;
	return ;
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
		temp->name = NULL; ////
		free(temp->value);
		temp->value = NULL;//////
		free(temp);
		temp = NULL;//////
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
