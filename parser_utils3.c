#include "minishell.h"

void	add_heredoc(t_list **here_doc, char *word)
{
	if (!(*here_doc))
		*here_doc = ft_lstnew(word);
	else
		ft_lstadd_back(here_doc, ft_lstnew(word));
}

void	parse_final(t_process **process, t_list **tmp)
{
	if ((*process)->argv)
		(*process)->args = list_to_array((*process)->argv);
	free_list_dp(tmp);
	if (process != NULL)
	{
		free (process);
		process = NULL;
	}
}

void	handle_command_pipe_redir(t_process **tmp_process, t_list **tmp)
{
	if ((*tmp)->content == NULL)
		return ;
	if (is_redir((*tmp)->content) == 1)
	{
		if ((*tmp)->next == NULL)
		{
			put_error(SINTAXERROR, 2);
			return ;
		}
		handle_redirection(tmp, *tmp_process);
	}
	else if (ft_strncmp((*tmp)->content, "|", 2) == 0)
	{
		if ((*tmp)->next == NULL)
		{
			put_error(SINTAXERROR, 2);
			return ;
		}
		handle_pipe(tmp_process, *tmp);
	}
	else
		handle_command(tmp_process, *tmp);
}
