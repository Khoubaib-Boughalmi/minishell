#include "../../minishell.h"

void	transforming_token_lst(t_token_lst *token_lst)
{
	
	printf("num_cmd %d\n", count_commands(token_lst));
	printf("num_red %d\n", count_redirections(token_lst));

}

char **create_lst_commands(t_token_lst *token_lst)
{
    int        i;
    int        j;
    char    **lst_cmd;

    j = -1;
    lst_cmd = (char **)malloc(sizeof(char *) * (count_commands(token_lst) + 1));
    if(!lst_cmd)
        return (0);
    while(token_lst && token_lst->token->type != AST_PIPE)
    {
        i = -1;
        if(token_lst->token->type == AST_COMMAND)
        {
            while (token_lst->token->args[++i])
                lst_cmd[++j] = token_lst->token->args[i]; 
        }
        token_lst = token_lst->next;
    }
    lst_cmd[j + 1] = 0;
    return (lst_cmd);
}

t_redirection    **create_lst_redirections(t_token_lst *token_lst)
{
    t_redirection    **lst_reds;
    int                i;

    i = -1;
    lst_reds = (t_redirection **)malloc(sizeof(t_redirection *) * (count_redirections(token_lst) + 1));
    if(!lst_reds)
        return (0);
     while(token_lst && token_lst->token->type != AST_PIPE)
    {
        if(token_lst->token->type == AST_REDIRECTION)
        {
            lst_reds[++i] = (t_redirection *)malloc(sizeof(t_redirection));
            if(!lst_reds[i])
                return (0);
            lst_reds[i]->value = token_lst->token->redirect_fname;
            lst_reds[i]->type = token_lst->token->red_type;
        }
        token_lst = token_lst->next;
    }
    lst_reds[i + 1] = 0;
    return (lst_reds);
}

void executor(t_token_lst *token_lst)
{
	char **str;
	t_redirection **list_reds;
	int	i;
	t_token_lst *tmp1;

	i = -1;
	if(!token_lst)
		return ;
	tmp1 = token_lst;
	while (token_lst)
	{
		if (token_lst->token->type == AST_PIPE)
		{
			if (!token_lst->next)
				return ;
			token_lst = token_lst->next;
			ex_main(tmp1, token_lst);
			return ;
		}
		token_lst = token_lst->next;
	}
	dup2(gstruct->ppout, 1);
	str = create_lst_commands(tmp1);
	list_reds = create_lst_redirections(tmp1);
	int a1;
	signal(SIGINT, &sigint_hander_executor);
	a1 = fork();
	if (a1 == 0)
	{
		if(is_builtin(str[0]))
		{
			handle_builtin(str);
			exit(gstruct->exit_status);
		}
		if (redirect_in_out(list_reds))
			exit(gstruct->exit_status);
		if (str[0] && path_finder(str[0], gstruct->envp_head))
			execve(path_finder(str[0], gstruct->envp_head), str, get_envp_arr());
		else
			cmd_not_found(str);
	}
	waitpid(a1, &gstruct->exit_status, 0);
	close(gstruct->stin);
	close(gstruct->stout);
	while (wait(NULL) > 0);
	dup2(gstruct->ppout, 1);
	dup2(gstruct->ppin, 0);
}
