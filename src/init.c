/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:44:27 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/14 16:45:05 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_g_struct(void)
{
	g_struct = (t_global_struct *)malloc(sizeof(t_global_struct));
	if (!g_struct)
		return (0);
	ft_memset(g_struct, 0, sizeof(t_global_struct));
	g_struct->ppin = 0;
	g_struct->ppout = 1;
	return (1);
}

int	init_envp(char **envp)
{
	t_envp_node	*node;
	int			i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		node = envp_new_node(get_key(envp[i]), get_value(envp[i]), ENVP);
		if (!node)
			return (0);
		envp_lst_add_back(node, &(g_struct->envp_head));
		i++;
	}
	if (!duplicate_list_export())
		return (0);
	return (1);
}
