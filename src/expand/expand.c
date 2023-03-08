#include "../../minishell.h"

void	expand(t_token_lst *tokens_lst)
{
	t_envp_node	*tmp;
	int			i;
	int			j;

	tmp = NULL;
	while (tokens_lst)
	{
		i = -1;
		if(tokens_lst->token->type == AST_COMMAND)
		{
			while (tokens_lst->token->args[++i])
			{
				if(tokens_lst->token->args[i][0] == '$')
				{
					tmp = envp_find_node(&(tokens_lst->token->args[i][1]));
					if(tmp)
					{
						free(tokens_lst->token->args[i]);
						tokens_lst->token->args[i] = tmp->value;
					}
				}
			}	
		}
		else if(tokens_lst->token->type == AST_REDIRECTION)
		{
				if(tokens_lst->token->redirect_fname[0] == '$')
				{
					tmp = envp_find_node(&(tokens_lst->token->redirect_fname[1]));
					if(tmp)
					{
						free(tokens_lst->token->redirect_fname);
						tokens_lst->token->redirect_fname = tmp->value;
					}
				}
		}
		tokens_lst = tokens_lst->next;
	}
}
