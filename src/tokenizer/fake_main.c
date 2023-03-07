#include "../../minishell.h"

/*
HOW TO USE : 
	copy the content of this main in the original main function and make. 
*/
int fake_tokenize_main() // to be deleted later
{
	t_token_lst *token;

	token = tokenizer("ls -la || cat -e >> out.txt");
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
					printf("%s ", token->token->args[i]);
					i++;
				}
			}
			else
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
