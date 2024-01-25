#include "minishell.h"


/*Para comprobar si las comillas están cerradas
	Devuelve:
		0 si no hay comillas
		1 si las comillas están abiertas
		2 si las comillas están cerradas
	
	El segundo argumento sirve para saber si ha habido comillas previas
*/
int	check_closed_quotes(char *line, int q, int i)
{
	char	quot;
	char	d_quot;
	char	in_quot;

	quot = 39;
	d_quot = 34;
	in_quot = 0;
	while (line[i])
	{
		printf("line[%d] = %c\n", i, line[i]);
		if (line[i] == quot || line[i] == d_quot)
		{
			q = 1;
			if (line[i] == d_quot)
				in_quot = '"';
			else
				in_quot = '\'';
			i++;
			while (line[i])
			{
				if (line[i] == in_quot)
				{
					q = 2;
					i++;
					if (line[i] != '\0')
					{
						q = check_closed_quotes(line, 2, i);
						return (q);
					}
				}
				else
				i++;
			}
		}
		i++;
	}
	return (q);
}
