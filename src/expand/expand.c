#include "../../minishell.h"

void	expand(t_token_lst *tokens_lst)
{
	char	*tmp;
	int		i;
	int		j;
	while (tokens_lst)
	{
		i = -1;
		if(tokens_lst->token->type == AST_COMMAND)
		{
			while (tokens_lst->token->args[++i])
			{
				if(tokens_lst->token->args[i][0] == '$')
				{
					tmp = envp_find_node(&(tokens_lst->token->args[i][1]))->value;
					if(!tmp)
						return ;
					free(tokens_lst->token->args[i]);
					tokens_lst->token->args[i] = tmp;
				}
			}	
		}
		else if(tokens_lst->token->type == AST_REDIRECTION)
		{
				if(tokens_lst->token->redirect_fname[0] == '$')
				{
					tmp = envp_find_node(&(tokens_lst->token->redirect_fname[1]))->value;
					if(!tmp)
						return ;
					free(tokens_lst->token->redirect_fname);
					tokens_lst->token->redirect_fname = tmp;
				}
		}
		tokens_lst = tokens_lst->next;
	}
}

//echo $PATH | cat -e >> file.txt
