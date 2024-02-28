#include "minishell.h"

void	put_error(int error_type, int error_code)
{
	g_exit_status = error_code;
	if (error_type == DEQUOTE)
		perror("minishell: error: dequoted line\n");
	else if (error_type == NOTFILEORDIR)
		perror("minishell: error: No such file or directory\n");
	else if (error_type == NOTPERMISSION)
		perror("minishell: error: Permission denied\n");
	else if (error_type == NOTCOMMAND)
		perror("minishell: error: command not found\n");
	else if (error_type == DUPERROR)
		perror("minishell: error: fd duplication failed\n");
	else if (error_type == FORKERROR)
		perror("minishell: error: fork failed\n");
	else if (error_type == PIPEERROR)
		perror("minishell: error: pipe failed\n");
	else if (error_type == UNEXPECTEDTOKEN)
		perror("minishell: error: syntax error near unexpected token\n");
	else if (error_type == MEMPROBLEM)
		perror("minishell: error: memory allocation failed\n");
	else if (error_type == ISDIR)
		perror("minishell: error: Is a directory\n");
	else if (error_type == NOTDIR)
		perror("minishell: error: Not a directory\n");
	else if (error_type == OPENERROR)
		perror("minishell: error: open failed\n");
}
