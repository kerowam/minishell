#include "minishell.h"

int	get_int_length(int value)
{
	int	length;

	length = 1;
	while (value != 0)
	{
		value /= 10;
		length++;
	}
	return (length);
}

// Función para convertir un entero a una cadena de caracteres
void	int_to_str(char *buffer, int value)
{
	int	length;
	int	i;

	length = get_int_length(value);
	buffer[length] = '\0';
	i = length - 1;
	while (i >= 0)
	{
		buffer[i--] = '0' + value % 10;
		value /= 10;
	}
}

size_t	handle_percent(char *buffer, int *j, char *format, void *args[])
{
	if (format[0] == '%' && format[1] != '\0')
	{
		if (format[1] == 'd')
		{
			int_to_str(buffer + *j, *((int *)args[0]));
			*j += get_int_length(*((int *)args[0]));
			return (2);
		}
		else if (format[1] == 's')
			return (handle_string(buffer, j, (char *)args[0]));
		else
		{
			buffer[(*j)++] = format[0];
			return (1);
		}
	}
	else
	{
		buffer[(*j)++] = format[0];
		return (1);
	}
}

size_t	handle_string(char *buffer, int *j, char *str)
{
	int	k;

	k = 0;
	while (str[k] != '\0')
		buffer[(*j)++] = str[k++];
	return (2);
}

int	my_sprintf(char *buffer, char *format, void *args[])
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (format[i] != '\0')
		i += handle_percent(buffer, &j, format + i, args);
	buffer[j] = '\0';
	return (j);
}
