#include "../../minishell.h"

int	ft_check_mul_pipe(char	*input, t_token_lst *tokens_lst)
{
	int		i;
	int		j;
	char	n;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '|')
			break ;
		if (input[i] == '|')
			return (1);
		i++;
	}
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			n = input[i];
			i++;
			while (!input[i] || (input[i] != n && input[i] != n))
				i++;
			if (input[i] == '\0')
				return (1);
		}
		if (input[i] == '|')
		{
			j = i + 1;
			while(input[j] == ' ')
				j++;
			while (input[j])
			{
				if (input[j] == '|')
					return (1);
				else
					break ;
				j++;
			}
		}
		i++;
	}
	t_token_lst *tmp;

	tmp = tokens_lst;
	if (tmp->token->type == AST_PIPE)
		return 1;
	while (tmp)
	{
		if (tmp->token->type == AST_REDIRECTION)
		{
			if (tmp->token->redirect_fname == NULL)
				return 1;
		}
		if (tmp->token->type == AST_PIPE)
		{
			if (tmp->next == NULL)
				return 1;
		}
		if (tmp->token->type == AST_COMMAND)
		{
			if (tmp->token->args[0] == NULL)
				return 1;
		}
		tmp = tmp->next;
	}
	return (0);
}
