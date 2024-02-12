#include "minishell.h"

void	signals_handler(int sign)
{
	if (sign == SIGCHLD)
	{
		// Manejo de cambios en los estados de los hijos
		// Obtener info adicional o actualizar estado shell
	}
	else if (sign == SIGINT)
	{
		// Manejo señal interrupcion (Ctrl + C)
	}
	// Mas casos si necesario
}

void	setup_signal_handlers(void)
{
	signal(SIGCHLD, signals_handler);
	signal(SIGINT, signals_handler);
}
