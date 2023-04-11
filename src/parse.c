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

int	is_builtin2(char	*cmd)
{
	int	i;
	char	**builtins;

	i = 0;
	
	builtins = ft_split("cd exit export unset", ' ');
	if(!builtins)
		return (0);
	
	while (builtins[i])
	{
		if(cmd)
		{
			if(!ft_strlcmp(builtins[i], cmd))
			{
				free_split(builtins);
				return (1);
			}
		}
		i++;
	}
	free_split(builtins);
	return (0);
}

int	tokenize_expand_execute(char *input)
{
	t_token_lst *tokens_lst;

	if (syntax_errors(input))
    {
        gstruct->exit_status = 2;
        return 1;
    }
	tokens_lst = tokenize(input);
	if (!tokens_lst)
	 	return 1;
    if (ft_check_mul_pipe(input, tokens_lst))
    {
        ft_putstr_fd("minishell: syntax error\n", 2);
        gstruct->exit_status = 2;
        return 1;
    }
	gstruct->tokens_head = tokens_lst;
	// ft_export_with_args("", "myValue");
	expand(tokens_lst);
	// clean_expand_args(tokens_lst);
	gstruct->ppin = dup(0);
	gstruct->ppout = dup(1);
	if (is_pipe(tokens_lst))
		executor(tokens_lst);
	else{
		char **str;
		t_redirection **list_reds;
		str = create_lst_commands(tokens_lst);
		list_reds = create_lst_redirections(tokens_lst);
		if(is_builtin2(str[0]))
			handle_builtin(str);
		else
		{
			int a1;
			signal(SIGINT, &sigint_hander_executor);
			a1 = fork();
			if (a1 == 0)
			{
				if (redirect_in_out(list_reds))
				{
					exit(gstruct->exit_status);
				}
				if (is_builtin(str[0]))
				{
					handle_builtin(str);
					exit(gstruct->exit_status);
				}
				else if (str[0] && path_finder(str[0], gstruct->envp_head))
				{
					if (access(path_finder(str[0], gstruct->envp_head), F_OK) < 0)
					{
						ft_printf("minishell: No such file or directory\n");
						exit(127);
					}
					if (access(path_finder(str[0], gstruct->envp_head), X_OK) < 0)
					{
						ft_printf("minishell: %s: Permission denied\n", str[0]);
						exit(126);
					}
					execve(path_finder(str[0], gstruct->envp_head), str, get_envp_arr());
				}
				else if (str[0])
					cmd_not_found(str);
				exit (0);
			}
			waitpid(a1, &gstruct->exit_status, 0);
			if(WIFEXITED(gstruct->exit_status))
				gstruct->exit_status = WEXITSTATUS(gstruct->exit_status);
			else if (WIFSIGNALED(gstruct->exit_status))
				gstruct->exit_status = WTERMSIG(gstruct->exit_status) + 127;
		}
	}
	return (1);
}