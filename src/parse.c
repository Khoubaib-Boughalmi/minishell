#include "../minishell.h"

void	parse_and_execute(char *input)
{

	t_token_lst *tokens_lst;
	
	tokens_lst = tokenizer(input);
	display_tokens(tokens_lst);
}