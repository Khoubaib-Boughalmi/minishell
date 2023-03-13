#include "../../minishell.h"

void	expand_variables(char *original, char	*copy, t_token_type token_type)
{
	t_envp_node	*tmp;
	char	*expanded_exit;

	int			i;
	int			j;

	tmp = NULL;

	i = 0;
	// if(token_type == AST_COMMAND)
	// {
		// while (copy[++i])
		// {
			// if(copy[1] == '?')
			// 	expand_exit_status(tokens_lst, i);
			// else
			// {
				tmp = envp_find_node(&(copy[1]), get_variable_len(&(copy[1])));
				// printf("len :%d\n", get_copy_len(&(copy[1])));
				if(tmp)
				{
					// free(copy);
					printf("%s", tmp->value);
					// copy = tmp->value;
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
