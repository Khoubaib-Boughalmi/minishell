#include "../../minishell.h"

void	expand_variables(char	*key, t_token_type token_type)
{
	t_envp_node	*tmp;
	char	*expanded_exit;

	int			i;
	int			j;

	tmp = NULL;

	i = 0;
	// if(token_type == AST_COMMAND)
	// {
		// while (key[++i])
		// {
			// if(key[1] == '?')
			// 	expand_exit_status(tokens_lst, i);
			// else
			// {
				tmp = envp_find_node(&(key[1]), get_key_len(&(key[1])));
				if(tmp)
				{
					// free(key[i]);
					printf("%s", tmp->value);
					// key[i] = tmp->value;
				}
			// }
		// }	
	// }
		// else if(tokens_lst->token->type == AST_REDIRECTION)
		// {
		// 		if(tokens_lst->token->redirect_fname[0] == '$')
		// 		{
		// 			tmp = envp_find_node(&(tokens_lst->token->redirect_fname[1]));
		// 			if(tmp)
		// 			{
		// 				free(tokens_lst->token->redirect_fname);
		// 				tokens_lst->token->redirect_fname = tmp->value;
		// 			}
		// 		}
		// }
}
