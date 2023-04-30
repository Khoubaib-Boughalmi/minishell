/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:38:32 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/30 18:38:59 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	duplicate_list_export(void)
{
	int			i;
	t_envp_node	*node;
	t_envp_node	*envp_ptr;

	if (!g_struct->envp_head)
		return (0);
	envp_ptr = g_struct->envp_head;
	while (envp_ptr)
	{
		node = envp_new_node(envp_ptr->key, envp_ptr->value, ENVP);
		envp_lst_add_back(node, &(g_struct->export_head));
		envp_ptr = envp_ptr->next;
	}
	return (1);
}
