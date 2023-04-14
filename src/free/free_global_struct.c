#include "../../minishell.h"

void	free_token_lst()
{
	int			i;
	t_token_lst	*ptr;
	t_token_lst	*current;

	i = -1;
	current = g_struct->tokens_head;
	if(!current)
		return;
	ptr = current->next;
	while(ptr)
	{
		if(current->token->type == AST_COMMAND)
			free_split(current->token->args);
		else if(ptr->token->type == AST_REDIRECTION)
		{
			free(ptr->token->redirect_fname);
			free(ptr->token->redirect_fd);
		}
		free(current);
		current = ptr;
		ptr = ptr->next;
	}
}

void	free_envp_lst()
{
	int			i;
	t_envp_node	*ptr;
	t_envp_node	*current;

	i = -1;
	current = g_struct->envp_head;
	if(!current)
		return;
	ptr = current->next;
	while(current)
	{
		free(current->key);
		free(current->value);
		free(current);
		current = ptr;
		if(ptr)
			ptr = ptr->next;
	}
}


void	free_export_lst()
{
	int			i;
	t_envp_node	*ptr;
	t_envp_node	*current;

	i = -1;
	current = g_struct->export_head;
	if(!current)
		return;
	ptr = current->next;
	while(current)
	{
		free(current->key);
		free(current->value);
		free(current);
		current = ptr;
		if(ptr)
			ptr = ptr->next;
	}
}

void	free_cmds_reds_array()
{
	int	i;

	i = -1;
	if(g_struct->list_cmds)
		free_split(g_struct->list_cmds);
}

void	free_global_struct()
{
	free(g_struct->src_input);
	free_token_lst();
	free_cmds_reds_array();
	free_envp_lst();
	free_export_lst();
	free(g_struct);
}

//  total heap usage: 675 allocs, 401 frees, 228,710 bytes allocated