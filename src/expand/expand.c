#include "../../minishell.h"

void	expand(t_token_lst *tokens_lst)
{
	t_envp_node	*tmp;
	char	*expanded_exit;

	int			i;
	int			j;

	tmp = NULL;
	//ft_env();
	while (tokens_lst)
	{
		i = -1;
		if(tokens_lst->token->type == AST_COMMAND)
		{
			// ====> previously used to handle ambigious redirection
			// while (tokens_lst->token->args[++i] && ft_strlcmp(tokens_lst->token->args[0], "export"))
			while (tokens_lst->token->args[++i])
				expand_quotes(&(tokens_lst->token->args[i]), tokens_lst->token->type);
		}
		else if(tokens_lst->token->type == AST_REDIRECTION)
		{
				// if(tokens_lst->token->redirect_fname[0] == '$')
				// {
				// 	tmp = envp_find_node(&(tokens_lst->token->redirect_fname[1]), 0);
				// 	if(tmp)
				// 	{
				// 		free(tokens_lst->token->redirect_fname);
				// 		tokens_lst->token->redirect_fname = tmp->value;
				// 	}
				// }
				if(tokens_lst->token->redirect_fname)
					expand_quotes(&(tokens_lst->token->redirect_fname), tokens_lst->token->type);
		}
		tokens_lst = tokens_lst->next;
	}
}