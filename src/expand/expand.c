#include "../../minishell.h"

void	expand(t_token_lst *tokens_lst)
{
	char	*temp;
	int		i;
	int		j;
	while (tokens_lst)
	{
		i = -1;
		if(tokens_lst->token->type != AST_PIPE)
		{
			while (tokens_lst->token->args[++i])
			{
				if(tokens_lst->token->args[i][0] == '$')
				{
					temp = envp_find_node(&(tokens_lst->token->args[i][1]));
					free(tokens_lst->token->args[i]);
					tokens_lst->token->args[i] = temp;
				}
			}	
		}
		tokens_lst = tokens_lst->next;
	}
}

//echo $PATH | cat -e >> file.txt
