#include "../../minishell.h"

void	expand(t_token_lst *tokens_lst)
{
	t_envp_node	*tmp;
	char	*expanded_exit;

	int			i;
	int			j;

	tmp = NULL;
	while (tokens_lst)
	{
		i = -1;
		if(tokens_lst->token->type == AST_COMMAND)
		{
			while (tokens_lst->token->args[++i])
				expand_quotes(&(tokens_lst->token->args[i]), tokens_lst->token->type, &tokens_lst->token->to_trim);
		}
		else if(tokens_lst->token->type == AST_REDIRECTION)
		{
				if(tokens_lst->token->redirect_fname && tokens_lst->token->red_type != HEREDOC)
					expand_redirection_fname(tokens_lst->token);
		}
		tokens_lst = tokens_lst->next;
	}
}