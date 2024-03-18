#include "minishell.h"

extern int	g_status;

void	signals_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_status = 130;
		printf("\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
