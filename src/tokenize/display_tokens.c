#include "../../minishell.h"

void	display_tokens(t_token_lst *tokens_lst)
{
	int	i;

	i = 0;
	while(tokens_lst)
	{
		i = 0;
		if(tokens_lst->token->args)
		{
			if(tokens_lst->token->type == AST_COMMAND)
			{
				printf("COMMAND: ");
				while (tokens_lst->token->args[i] != 0)
				{
					printf("[%d]: %s ", i, tokens_lst->token->args[i]);
					i++;
				}
			}
			else if(tokens_lst->token->type == AST_PIPE)
			{
				printf("PIPE: ");
				while (tokens_lst->token->args[i] != 0)
				{
					printf("%s ", tokens_lst->token->args[i]);
					i++;
				}

			}			
		}
		if (tokens_lst->token->type == AST_REDIRECTION) 
			printf("REDIR: %s %s", tokens_lst->token->redirect_fd, tokens_lst->token->redirect_fname);
		printf("\n");
		tokens_lst = tokens_lst->next;
	}
	return ;
}