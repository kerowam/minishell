/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:21:54 by nmontiel          #+#    #+#             */
/*   Updated: 2024/01/19 16:37:05 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_command(char *path)
{
	if (chdir(path) != 0)
		perror("Error changing directory");
}
//falta hacer que se actualice pwd cada vexz que cambie de directorio.

int	find_env_var(char **environ, char *name)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)) == 0
			&& environ[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

//Elimina una variable de entorno existente
void	delete_env_var(char **environ, int index)
{
	int	i;

	i = index;
	while (environ[i] != NULL)
	{
		environ[i] = environ[i + 1];
		i++;
	}
}

//Agrega una nueva variable de entorno
void	add_env_var(char **environ, char *new_var)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	environ[i] = ft_strdup(new_var);
	environ[i + 1] = NULL;
}

//Esta es la función export
void	export_func(char ***environ, char *input)
{
	char	*name;
	char 	*value;
	char	*equal_sign;
	int		index;

	name = NULL;
	value = NULL;
	equal_sign = ft_strchr(input, '=');
	if (equal_sign != NULL)
	{
		name = malloc(equal_sign - input + 1);
		ft_strlcpy(name, input, equal_sign - input);
		name[equal_sign - input] = '\0';
		value = ft_strdup(equal_sign + 1);
		if (name != NULL && value != NULL)
		{
			index = find_env_var(*environ, name);
			if (index != -1)
			{
				free((*environ)[index]);
				(*environ)[index] = strdup(input);
			}
			else
				add_env_var(*environ, input);
		}
		else
			printf("Error: Formato inválido. Debe ser 'nombre=valor'.\n");
		free(name);
		free(value);
	}
	else
		fprintf(stderr, "Error: Formato inválido. Debe ser 'nombre=valor'.\n");
}

//Modificar caso "nombre"= "valor" de export y separar funcion.

//Arreglar unset para que funcione como debe y no haga cosas raras

//Añadir la actualizacion de pwd a cd una vez export funcione como debe funcionar.

//Mirar porque el prompt se borra al usar el historial.