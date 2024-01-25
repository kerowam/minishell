#include "minishell.h"

void	env_command(t_data *shell)
{
	t_env	*current_env;

	current_env = shell->env;
	while (current_env != NULL)
	{
		printf("%s%s\n", current_env->name, current_env->value);
		current_env = current_env->next;
	}
}

void	pwd_command(t_data *shell)
{
	if (getcwd(shell->cwd, sizeof(shell->cwd)) != NULL)
		printf("%s\n", shell->cwd);
	else
		perror("getcwd");
}
