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

int is_pipe(t_token_lst *tokens_lst)
{
	t_token_lst *tmp;

	tmp = tokens_lst;
	while (tmp)
	{
		if (tmp->token->type == AST_PIPE)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int	tokenize_expand_execute(char *input)
{
	t_token_lst *tokens_lst;

	tokens_lst = tokenize(input);
	if(!tokens_lst)
		return (0);
	gstruct->tokens_head = tokens_lst;
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
	if (is_pipe(tokens_lst))
		executor(tokens_lst);
	else{
		char **str;
		t_redirection **list_reds;
		str = create_lst_commands(tokens_lst);
		list_reds = create_lst_redirections(tokens_lst);
		if(is_builtin(str[0]))
		{
			if (redirect_in_out(list_reds))
				return (1);
			handle_builtin(str);
			dup2(gstruct->ppout, 1);
			dup2(gstruct->ppin, 0);
		}
		else
		{
			int a1;
			signal(SIGINT, &sigint_hander_executor);
			a1 = fork();
			if (a1 == 0)
			{
				if (redirect_in_out(list_reds))
					exit(gstruct->exit_status);
				if (str[0] && path_finder(str[0], gstruct->envp_head))
					execve(path_finder(str[0], gstruct->envp_head), str, get_envp_arr());
				else
					cmd_not_found(str);
			}
			waitpid(a1, &gstruct->exit_status, 0);
		}
	}
	return (1);
}
