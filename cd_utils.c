#include "minishell.h"

void	update_pwd(t_data *shell)
{
	t_env	*prov;
	char	dir[500];

	prov = shell->env;
	while (prov)
	{
		if (ft_strncmp(prov->name, "PWD", 6) == 0)
		{
			free(prov->value);
			getcwd(dir, sizeof(dir));
			prov->value = ft_strdup(dir);
			//printf("0. cd_utils prov->value pointer: %p\n", prov->value);
			if (!prov->value)
				return ;
			break ;
		}
		prov = prov->next;
	}
}

void	update_oldpwd(t_data *shell)
{
	t_env	*prov;
	char	dir[500];

	prov = shell->env;
	while (prov)
	{
		if (ft_strncmp(prov->name, "OLDPWD", 6) == 0)
		{
			free(prov->value);
			getcwd(dir, sizeof(dir));
			prov->value = ft_strdup(dir);
			//printf("0.1 cd_utils prov->value pointer: %p\n", prov->value);
			if (!prov->value)
				return ;
			break ;
		}
		prov = prov->next;
	}
}

void	update_oldpwd_again(t_data *shell, char *pwd)
{
	t_env	*prov;

	prov = shell->env;
	while (prov)
	{
		if (ft_strncmp(prov->name, "OLDPWD", 6) == 0)
		{
			free(prov->value);
			prov->value = ft_strdup(pwd);
			//printf("0.2 cd_utils prov->value pointer: %p\n", prov->value);
			if (!prov->value)
				return ;
			break ;
		}
		prov = prov->next;
	}
}

void	obtain_env(t_data *shell, char *env_var)
{
	t_env	*prov;

	prov = shell->env;
	while (prov)
	{
		if (ft_strncmp(prov->name, env_var, ft_strlen(prov->name)) == 0)
		{
			shell->cd = ft_strdup(prov->value);
			//printf("0.3 cd_utils shell->cd pointer: %p\n", shell->cd);
			if (!shell->cd)
				return ;
			break ;
		}
		prov = prov->next;
	}
}
