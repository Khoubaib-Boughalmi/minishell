#include "../../minishell.h"

void	free_token_lst()
{
	int			i;
	t_token_lst	*ptr;
	t_token_lst	*current;

	i = -1;
	current = gstruct->tokens_head;
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

void	free_envp_nodes_lst()
{
	int			i;
	t_envp_node	*ptr;
	t_envp_node	*current;

	i = -1;
	current = gstruct->envp_head;
	if(!current)
		return;
	ptr = current->next;
	while(ptr)
	{
		free(current->key);
		free(current->value);
		free(current);
		current = ptr;
		ptr = ptr->next;
	}
}

void	free_cmds_reds_array()
{
	int	i;

	i = -1;
	free_split(gstruct->list_cmds);
	// while(gstruct->list_reds[++i])
	// 	free(gstruct->list_reds[i]->value);
	// free(gstruct->list_reds);
}

void	free_global_struct()
{
	free(gstruct->src_input);
	free_token_lst();
	free_cmds_reds_array();
	// free_envp_nodes_lst();
}

//  total heap usage: 675 allocs, 401 frees, 228,710 bytes allocated