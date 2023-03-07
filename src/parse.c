#include "../minishell.h"

int	tokenize_expand_execute(char *input)
{
	t_token_lst *tokens_lst;

	tokens_lst = tokenize(input);
	if(!tokens_lst)
		return (0);
	gstruct->tokens_head = tokens_lst;
	ft_export("myKey", "myValue");
	display_tokens(tokens_lst);
	printf("~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~\n");
	expand(tokens_lst);
	display_tokens(tokens_lst);
	return (1);
}