#include "../../minishell.h"


// void	expand_variables_handler(char **original, char *copy, int *i, t_token_type token_type)
// {
// 	if(copy[*i] == '$')
// 	{
// 		expand_variables(original, copy + *(i), token_type);
// 		while (copy[*i] && copy[*i] != ' ' && copy[*i] != '\"' && copy[*i] != '\'')
// 			*i += 1;
// 	}
// 	else
// 	{
// 		cbc_str_join(original, copy[*i]);
// 		*i += 1;
// 	}
// }

char	*trim_str(char *str)
{
	int	i;
	int	j;
	int	k;
	char	*new_str;

	if(!str)
		return NULL;
	i = 0;
	k = 0;
	j = ft_strlen(str) - 1;
	while (str[i] && str[i] == ' ')
		i++;
	while (j >= 0 && j >= i && str[j] == ' ')
		j--;
	new_str = (char *)malloc(sizeof(char) * (j - i + 1));
	k = 0;
	while (str[i] && i <= j)
	{
		new_str[k] = str[i];
		i++;
		k++;
	}
	printf("trimed\n");
	new_str[k] = '\0';
	return (new_str);
}

void	expand_variables(char **original, char	*copy, t_token_type token_type, t_trim trim)
{
	t_envp_node	*tmp;
	char	*expanded_exit;
	char	*trimed;

	int			i;
	int			j;

	tmp = NULL;
	i = 0;
			if(copy[1] == '?')
				expand_exit_status(original, &(copy[1]));
			else if(!copy[1] || copy[1] == ' ' || copy[1] == '|' )
				cbc_str_join(original, '$');
			else
			{
				tmp = envp_find_node(&(copy[1]), get_variable_len(&(copy[1])), gstruct->envp_head);
				if(tmp)
				{
					i = -1;
					if(trim)
					{
						trimed = trim_str(tmp->value);
						while (trimed[++i])
							cbc_str_join(original, trimed[i]);
					}
					else
					{
						while (tmp->value[++i])
							cbc_str_join(original, tmp->value[i]);
					}
				}
				// else
				// 	cbc_str_join(original, '$');
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
