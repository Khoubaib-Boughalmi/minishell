#include "../minishell.h"

// void 	clean_expand_args(t_token_lst *tokens_lst)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	while (tokens_lst)
// 	{
// 		if(tokens_lst->token->type == AST_COMMAND)
// 		{
// 			i = 0;
// 			while(tokens_lst->token->args[i])
// 			{
// 				if(!ft_strlcmp(tokens_lst->token->args[i], "$"))
// 				{
// 					free(tokens_lst->token->args[i]);
// 					j = i;
// 					while (tokens_lst->token->args[j])
// 					{
// 						tokens_lst->token->args[j] = tokens_lst->token->args[j + 1];
// 						j++;
// 					}
// 				}
// 				i++;
// 			}
// 		}
// 		tokens_lst = tokens_lst->next;
// 	}
	
// }

int	tokenize_expand_execute(char *input)
{
	t_token_lst *tokens_lst;

	tokens_lst = tokenize(input);
	if(!tokens_lst)
		return (0);
	// gstruct->tokens_head = tokens_lst;
	// ft_export_with_args("", "myValue");
	// ft_export_with_args("myKey", "");
	// ft_unest("myKey");
	// ft_export_with_args("myFile", "outfile.txt");
	// ft_env();
	// display_tokens(tokens_lst);
	// printf("~~~~~~~~~~~~~~~~\n");
	// printf("~~~~~~~~~~~~~~~~\n");
	expand(tokens_lst);
	// clean_expand_args(tokens_lst);
	// display_tokens(tokens_lst);
	// executor(tokens_lst);
	// create_lst_commands(gstruct->tokens_head);
	//ft_export_with_args((char *[]){"a1=1" , "a2=2" , "a3=0", "a3=45", "a3=0", NULL});
	// ft_export_with_args((char *[]){"1a1=12", NULL});
	// ft_unest((char *[]){"a1" , "a3", "a3", "a5", NULL});
	// ft_env();
	//ft_export_no_args();
	// printf("~~~~~~~~~~~~~~~~\n");
	// printf("~~~~~~~~~~~~~~~~\n");
	// ft_unest((char *[]){"a1" , "a3", "a3", "a5", NULL});
	// ft_env();
	// char **ptr = get_envp_arr();
	// int i = 0;
	// while (ptr[i])
	// {
	// 	printf("%s\n", ptr[i]);
	// 	i++;
	// }
	gstruct->ppin = dup(0);
	gstruct->ppout = dup(1);
	executor(tokens_lst);
	return (1);
}
