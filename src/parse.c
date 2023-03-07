#include "../minishell.h"

void	parse_and_execute(char *input)
{
	t_token_lst *token;

	token = tokenizer(input);
	int i = 0;
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