#include "../../minishell.h"

t_token_lst *ft_put_intoken(char **str)
{
	t_token_lst	*node;
	t_token_lst	*token;
	char **tmp;
	int i = 0;
	int j = 0;

	token = NULL;
	node = NULL;
	while(i < ft_count_str(str))
	{
		node = malloc(sizeof(t_token_lst));
		node->token = malloc(sizeof(t_token));
		if (ft_check_pipe(str[i]))
		{
			node->token->args = ft_split(str[i],' ');
			node->token->type = AST_PIPE;
			node->token->num_args = 0;
			node->token->redirect_fd = NULL;
			node->token->redirect_fname = NULL;
		}
		else if (ft_check_der(str[i]))
		{
			tmp = ft_split(str[i + 1],' ');
			node->token->redirect_fd = ft_strdup(str[i]);
			node->token->redirect_fname = ft_strdup(tmp[0]);
			node->token->args = NULL;
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
			node->token->redirect_fd = NULL;
			node->token->redirect_fname = NULL;
			node->token->type = AST_COMMAND;
		}
		ft_lst_token_add_back(&token, node);
		//free(node);
		i++;
	}
	// ft_free(str);
	return (token);
}

t_token_lst *tokenize(char	*input)
{
	t_token_lst	*token;
	char			**temp;

	token = NULL;
	temp = ft_split(input, '|');
	temp = ft_pipe_insert(temp);
	temp = ft_split_der(temp);
	token = ft_put_intoken(temp);

	return (token);
}
