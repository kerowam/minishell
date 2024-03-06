#include "minishell.h"

int	g_exit_status;

void	signals_handler(int sign)
{
	if (sign == SIGINT)
	
	{
		g_exit_status = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	/*else if (sign == SIGCHLD)
	{
		
	}
	// Mas casos si necesario*/
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGCHLD, signals_handler);
}
