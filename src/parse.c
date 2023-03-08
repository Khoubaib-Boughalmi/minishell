#include "../minishell.h"

int	tokenize_expand_execute(char *input)
{
	t_token_lst *tokens_lst;

	tokens_lst = tokenize(input);
	if(!tokens_lst)
		return (0);
	gstruct->tokens_head = tokens_lst;
	ft_export("myKey", "myValue");
	ft_export("myKey", "myValue");
	ft_export("myKey", "myValue2");
	ft_export("myFile", "outfile.txt");
	ft_env();
	display_tokens(tokens_lst);
	printf("~~~~~~~~~~~~~~~~\n");
	// printf("~~~~~~~~~~~~~~~~\n");
	expand(tokens_lst);
	display_tokens(tokens_lst);
	return (1);
}

//try this : ls -la | hello $PATH | echo $myKey