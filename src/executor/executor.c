#include "../../minishell.h"

int	create_lst_commands(t_token_lst *token_lst)
{
	int	i;
	int	j;

	j = -1;
	if(gstruct->list_cmds)
		free(gstruct->list_cmds);
	gstruct->list_cmds = (char **)malloc(sizeof(char *) * (count_commands(token_lst) + 1));
	if(!gstruct->list_cmds)
		return (0);
	while(token_lst && token_lst->token->type != AST_PIPE)
	{
		i = -1;
		if(token_lst->token->type == AST_COMMAND)
		{
			while (token_lst->token->args[++i])
				gstruct->list_cmds[++j] = token_lst->token->args[i]; 
		}
		token_lst = token_lst->next;
	}
	gstruct->list_cmds[j + 1] = NULL;
	return (1);
}

int	create_lst_redirections(t_token_lst *token_lst)
{
	int	i;

	i = -1;
	if(gstruct->list_reds)
		free(gstruct->list_reds);
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
	gstruct->list_reds[i + 1] = NULL;
	return (1);
}

void executor(t_token_lst *token_lst)
{
	int	i;

	i = -1;
	if(!token_lst)
		return ;
	create_lst_commands(token_lst);
	create_lst_redirections(token_lst);
	while(gstruct->list_reds[++i])
		printf("red %s\n", gstruct->list_reds[i]->value);
	i = -1;
	while(gstruct->list_reds[++i])
		printf("cmd %s\n", gstruct->list_cmds[i]);
}