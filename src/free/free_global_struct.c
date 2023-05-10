/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_global_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:19:03 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/10 17:26:41 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	free_token_lst(t_token_lst *token_lst)
// {
// 	int			i;
// 	t_token_lst	*ptr;
// 	t_token_lst	*current;

// 	i = -1;
// 	current = token_lst;
// 	if (!current)
// 		return ;
// 	ptr = current;
// 	while (ptr)
// 	{
// 		if (current->token->type == AST_COMMAND)
// 		{
// 			if(current->token->args)
// 			{
// 				// printf("heheh %s\n", current->token->args[0]);
// 				free_split(current->token->args);
// 			}
// 		}
// 		else if (ptr->token->type == AST_PIPE)
// 			free_split(current->token->args);
// 		else if (ptr->token->type == AST_REDIRECTION)
// 		{
// 			if(ptr->token->redirect_fname)
// 				free(ptr->token->redirect_fname);
// 			free(ptr->token->redirect_fd);
// 		}
// 		ptr = ptr->next;
// 		// free(current->token);
// 		// free(current);
// 		// if(ptr)
// 			current = ptr;
// 	}
// }
void	free_token_lst(t_token_lst *token_lst)
{
	int			i;
	t_token_lst	*ptr;
	t_token_lst	*current;

	i = -1;
	current = token_lst;
	if(!current)
		return;
	ptr = current;
	while(current)
	{
		if(current->token->type == AST_COMMAND)
		{
			if(current->token->args)
			{
				free_args(current, current->token->args);
			}
		}
		else if(current->token->type == AST_PIPE)
			free_split(current->token->args);
		else if(ptr->token->type == AST_REDIRECTION)
		{
			if(ptr->token->redirect_fname)
				free(ptr->token->redirect_fname);
			free(ptr->token->redirect_fd);
		}
		ptr = current->next;
		free(current->token);
		free(current);
		current = ptr;
	}
}

void	free_envp_lst(void)
{
	int			i;
	t_envp_node	*ptr;
	t_envp_node	*current;

	i = -1;
	current = g_struct->envp_head;
	if (!current)
		return ;
	ptr = current->next;
	while (current)
	{
		free(current->key);
		free(current->value);
		free(current);
		current = ptr;
		if (ptr)
			ptr = ptr->next;
	}
}

void	free_export_lst(void)
{
	int			i;
	t_envp_node	*ptr;
	t_envp_node	*current;

	i = -1;
	current = g_struct->export_head;
	if (!current)
		return ;
	ptr = current->next;
	while (current)
	{
		free(current->key);
		free(current->value);
		free(current);
		current = ptr;
		if (ptr)
			ptr = ptr->next;
	}
}

void	free_list_reds(t_redirection **list_reds)
{
	int	i;

	i = 0;
	while (list_reds[i])
	{
		if(list_reds[i]->value)
			free(list_reds[i]->value);
		free(list_reds[i]);
		i++;
	}
	free(list_reds);
}

void	free_cmds_reds_array(char **list_cmds, t_redirection **list_reds)
{
	int	i;

	i = -1;
	if (list_cmds)
		free_split(list_cmds);
	if (list_reds)
		free_list_reds(list_reds);
}

void	free_global_struct(void)
{
	// free(g_struct->src_input);
	// free_token_lst(t_token_lst *token_lst);
	// free_cmds_reds_array();
	// free_envp_lst();
	// free_export_lst();
	// free(g_struct);
}
