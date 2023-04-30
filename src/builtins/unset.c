/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:34 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/29 15:18:05 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset_core(char	**list_keys, int i, int j)
{
	t_envp_node	*ptr;

	ptr = g_struct->export_head;
	while (ptr)
	{
		if (!ft_strlcmp(ptr->key, list_keys[j]))
		{
			envp_delete_node(i, &g_struct->export_head);
			break ;
		}
		i++;
		ptr = ptr->next;
	}
	i = 0;
	ptr = g_struct->envp_head;
	while (ptr)
	{
		if (!ft_strlcmp(ptr->key, list_keys[j]))
		{
			envp_delete_node(i, &g_struct->envp_head);
			break ;
		}
		i++;
		ptr = ptr->next;
	}
}

void	ft_unset(char	**list_keys)
{
	int			j;

	j = 0;
	while (list_keys[++j])
	{
		if (!check_str(list_keys[j]))
		{
			g_struct->exit_status = 1;
			return ;
		}
		ft_unset_core(list_keys, 0, j);
	}
	g_struct->exit_status = 0;
}
