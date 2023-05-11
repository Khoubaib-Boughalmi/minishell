/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_global_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:19:03 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/10 19:19:38 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_token_lst_norm(t_token_lst *current)
{
	if (current->token->type == AST_COMMAND)
	{
		if (current->token->args)
			free_args(current, current->token->args);
	}
	else if (current->token->type == AST_PIPE)
		free_split(current->token->args);
	else if (current->token->type == AST_REDIRECTION)
	{
		if (current->token->redirect_fname)
			free(current->token->redirect_fname);
		free(current->token->redirect_fd);
	}
}

void	free_token_lst(t_token_lst *token_lst)
{
	int			i;
	t_token_lst	*ptr;
	t_token_lst	*current;

	i = -1;
	current = token_lst;
	if (!current)
		return ;
	ptr = current;
	while (current)
	{
		free_token_lst_norm(current);
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
