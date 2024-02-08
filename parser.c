#include "minishell.h"

// Esta es una idea de como seria la funcion principal (por ahora) falta añadir
// las funciones mencionadas dentro y mas cosas, por ahora es para guiarme y empezar

void	parse_commands(t_list **words_splited)
{
	t_list		**current_token;
	t_list		**cmds;
	char		*current_command;
	t_process	*new_process;

	current_token = words_splited;
	cmds = (t_list **)malloc(sizeof(t_list *));
	*cmds = NULL;
	while (*current_token != NULL)
	{
		// Analizar el token y realizar acciones segun sea necesario
		current_command = (char *)(*current_token)->content;
		// Si es un comando
		if (is_command(current_command))
		{
			// Crea un nuevo nodo y configura los valores necesarios
			new_process = create_process(current_command);
			// Agrega el nuevo proceso a la lista de comandos
			add_process(cmds, new_process);
			// Avanza al siguiente token
			current_token = &((*current_token)->next);
		}
		// Si es una redireccion
		else if (is_redirection(current_command))
		{
			// Aqui se añade la logica para manejar las redirecciones

			// Al final avanza al siguiente token
			current_token = &((*current_token)->next);
		}
		// Otros casos
		else
		{
			// La logica para cada caso necesario

			// Avanza al siguiente token al final
			current_token = &((*current_token)->next);
		}
	}
	// Termina liberando los recursos necesarios y acaba el programa
}

// Seguramente hagan falta mas funciones auxiliares (como las mencionadas arriba)
// pero eso se ira añadiendo mientas avancemos con el parser