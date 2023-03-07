#include "minishell.h"

t_token_list *ft_put_intoken(char **str)
{
	t_token_list	*node;
	t_token_list	*token;
	char **tmp;
	int i = 0;
	int j = 0;

	token = NULL;
	while(i < ft_count_str(str))
	{
		node = malloc(sizeof(t_token_list));
		node->token = malloc(sizeof(t_token));
		if (ft_check_pipe(str[i]))
		{
			node->token->args = ft_split(str[i],' ');
			node->token->type = AST_PIPE;
			node->token->num_args = 0;
			node->token->redirect_fd = 0;
			node->token->redirect_fname = 0;
		}
		else if (ft_check_der(str[i]))
		{
			tmp = ft_split(str[i + 1],' ');
			node->token->redirect_fd = ft_strdup(str[i]);
			node->token->redirect_fname = ft_strdup(tmp[0]);
			node->token->args = 0;
			node->token->num_args = 0;
			i++;
			node->token->type = AST_REDIRECTION;
		}
		else 
		{
			node->token->args = ft_split(str[i],' ');
			while(node->token->args[j])
				j++;
			node->token->num_args = j;
			node->token->redirect_fd = 0;
			node->token->redirect_fname = 0;
			token->token->type = AST_COMMAND;
		}
		ft_lstadd_back(&token, node);
		//free(node);
		i++;
	}
	// ft_free(str);
	return (token);
}

t_token *ft_tokenization(char	*input)
{
	t_token	*token;
	char **temp;

	temp = ft_split(input, '|');
	temp = ft_pipe_insert(temp);
	temp = ft_split_der(temp);
	token = ft_put_intoken(temp);

	return (token);
}
