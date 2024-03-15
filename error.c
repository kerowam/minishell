#include "minishell.h"

extern int	g_status;

void	put_error(int error_type, int error_code)
{
	g_status = error_code;
	if (error_type == DEQUOTE)
		printf("minishell: error: dequoted line\n");
	else if (error_type == NOTFILEORDIR)
		printf("minishell: error: No such file or directory\n");
	else if (error_type == NOTPERMISSION)
		printf("minishell: error: Permission denied\n");
	else if (error_type == NOTCOMMAND)
		printf("minishell: error: command not found\n");
	else if (error_type == DUPERROR)
		printf("minishell: error: fd duplication failed\n");
	else if (error_type == FORKERROR)
		printf("minishell: error: fork failed\n");
	else if (error_type == PIPEERROR)
		printf("minishell: error: pipe failed\n");
	else if (error_type == UNEXPECTEDTOKEN)
		printf("minishell: error: syntax error near unexpected token\n");
	else if (error_type == MEMPROBLEM)
		printf("minishell: error: memory allocation failed\n");
	else if (error_type == ISDIR)
		printf("minishell: error: Is a directory\n");
	else if (error_type == NOTDIR)
		printf("minishell: error: Not a directory\n");
}

void	put_error2(int error_type, int error_code)
{
	g_status = error_code;
	if (error_type == NUMARG)
		printf("minishell: exit: a: numeric argument required.\n");
	else if (error_type == TOMANYARG)
		printf("minishell: exit: too many arguments\n");
	else if (error_type == NOTVALID)
		printf("minishell: is not a valid identifier\n");
	else if (error_type == OPENERROR)
		printf("minishell: error: open failed\n");
	else if (error_type == ARGS)
		printf("minishell: error: wrong number of arguments\n");
	else if (error_type == CLOSEERROR)
		printf("minishell: error: close failed\n");
	else if (error_type == SINTAXERROR)
		printf("minishell: error sintáctico cerca del elemento inesperado `newline'\n");
}
