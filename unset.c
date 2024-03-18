#include "minishell.h"

void unset2(t_env *del, t_env *aux, t_env *prev, t_data *shell)
{
	del = aux;
	if (prev)
		prev->next = aux->next;
	else
		shell->env = aux->next;
	free(del->name);
	free(del->value);
	free(del);
	//g_status = 0;
}

void	unset_command(t_data *shell, char *name)
{
	t_env	*aux;
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	del = NULL;
	aux = shell->env;
	prev = NULL;
	while (aux)
	{
		if (strcmp(aux->name, name) == 0)
		{
			unset2(del, aux, prev, shell);
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}
