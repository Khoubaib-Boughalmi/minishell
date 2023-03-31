#include "../../minishell.h"

void	transforming_token_lst(t_token_lst *token_lst)
{
	
	printf("num_cmd %d\n", count_commands(token_lst));
	printf("num_red %d\n", count_redirections(token_lst));

}

int	create_lst_commands(t_token_lst *token_lst)
{
	int	i;
	int	j;

	j = -1;
	gstruct->list_cmds = (char **)malloc(sizeof(char *) * (count_commands(token_lst) + 1));
	if(!gstruct->list_cmds)
		return (0);
	while(token_lst && token_lst->token->type != AST_PIPE)
	{
		i = -1;
		if(token_lst->token->type == AST_COMMAND)
		{
			while (token_lst->token->args[++i])
			{
				gstruct->list_cmds[++j] = token_lst->token->args[i]; 

			}
		}
		token_lst = token_lst->next;
	}
	gstruct->list_cmds[j + 1] = 0;
	return (1);
}

int	create_lst_redirections(t_token_lst *token_lst)
{
	int	i;

	i = -1;
	gstruct->list_reds = (t_redirection **)malloc(sizeof(t_redirection *) * (count_redirections(token_lst) + 1));
	if(!gstruct->list_reds)
		return (0);
	 while(token_lst && token_lst->token->type != AST_PIPE)
	{
		if(token_lst->token->type == AST_REDIRECTION)
		{
			gstruct->list_reds[++i] = (t_redirection *)malloc(sizeof(t_redirection));
			if(!gstruct->list_reds[i])
				return (0);
			gstruct->list_reds[i]->value = token_lst->token->redirect_fname;
			gstruct->list_reds[i]->type = token_lst->token->red_type;
		}
		token_lst = token_lst->next;
	}
	gstruct->list_reds[i + 1] = 0;
	return (1);
}
void executor(t_token_lst *token_lst)
{

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
			token_lst = token_lst->next;
			ex_main(tmp1, token_lst);
			return ;
		}
		token_lst = token_lst->next;
	}
	int a1;
	a1 = fork();
	if (a1 == 0)
	{
		create_lst_commands(tmp1);
		create_lst_redirections(tmp1);
		redirect_in_out(gstruct->list_reds);
		if (gstruct->list_cmds[0] && path_finder(gstruct->list_cmds[0], gstruct->envp_head))
			execve(path_finder(gstruct->list_cmds[0], gstruct->envp_head), gstruct->list_cmds, NULL);
		else
			cmd_not_found(gstruct->list_cmds);
	}
	waitpid(a1, NULL, 0);
	dup2(gstruct->ppin, 0);
}
