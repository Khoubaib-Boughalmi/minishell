#include "../../minishell.h"

void	display_tokens(t_token_lst *token)
{
	int	i;

	i = 0;
	while(token)
	{
		i = 0;
		if(token->token->args)
		{
			if(token->token->type == AST_COMMAND)
			{
				printf("COMMAND: ");
				while (token->token->args[i] != 0)
				{
					printf("[%d]: %s ", i, token->token->args[i]);
					i++;
				}
			}
			else if(token->token->type == AST_PIPE)
			{
				printf("PIPE: ");
				while (token->token->args[i] != 0)
				{
					printf("%s ", token->token->args[i]);
					i++;
				}

			}			
		}
		if(token->token->type == AST_REDIRECTION)
		{
			printf("REDIR: %s %s", token->token->redirect_fd, token->token->redirect_fname);
		}
		printf("\n");
		token = token->next;
	}
}