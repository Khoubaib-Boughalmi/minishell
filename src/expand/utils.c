#include "../../minishell.h"

void expand_exit_status(t_token_lst *tokens_lst, int i)
{
	char	*expanded_exit;

	if(ft_strlen(tokens_lst->token->args[i]) > 2)
	{
		expanded_exit = ft_strjoin(ft_itoa(gstruct->exit_status), &(tokens_lst->token->args[i][2]));
		free(tokens_lst->token->args[i]);
		tokens_lst->token->args[i] = expanded_exit;
	}
	else
	{
		free(tokens_lst->token->args[i]);
		tokens_lst->token->args[i] = ft_itoa(gstruct->exit_status);
	}
}
