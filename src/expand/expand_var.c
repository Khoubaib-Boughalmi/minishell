#include "../../minishell.h"


void	expand_variables_handler(char **original, char *copy, int *i, t_token_type token_type)
{
	if(copy[*i] == '$')
	{
		expand_variables(original, copy + *(i), token_type);
		while (copy[*i] && copy[*i] != ' ' && copy[*i] != '\"' && copy[*i] != '\'')
			*i += 1;
	}
	else
	{
		cbc_str_join(original, copy[*i]);
		*i += 1;
	}
}

void	expand_variables(char **original, char	*copy, t_token_type token_type)
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
			if(copy[1] == '?')
				expand_exit_status(original, &(copy[1]));
			else
			{
				tmp = envp_find_node(&(copy[1]), get_variable_len(&(copy[1])), gstruct->export_head);
				// printf("tmp :%s\n", tmp->value);

				if(tmp)
				{
					// free(copy);
					i = -1;
					// printf("%s\n", tmp->value);
					// printf("original %s\n", *original);
					while (tmp->value[++i])
						cbc_str_join(original, tmp->value[i]);
					// copy = tmp->value;
				}
			}
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
