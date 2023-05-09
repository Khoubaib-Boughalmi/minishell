/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:48:35 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/09 21:11:23 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd_core(void)
{
	t_envp_node	*home_node;

	home_node = envp_find_node("HOME", ft_strlen("HOME"), \
	g_struct->envp_head);
	if (!home_node)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (0);
	}
	if (chdir(home_node->value))
	{
		ft_printf("minishell: %s: No such file or directory\n", \
		home_node->value);
		g_struct->exit_status = 1;
		return (0);
	}
	return (0);
}

void	ft_cd(char **list_vars)
{
	if (list_vars_len(list_vars) > 2)
	{
		ft_printf("cd: too many arguments\n");
		g_struct->exit_status = 1;
	}
	else
	{
		if (!list_vars[1] || !ft_strlcmp(list_vars[1], "~"))
		{
			if (!ft_cd_core())
				return ;
		}
		if (chdir(list_vars[1]))
		{
			perror("minishell: ");
			g_struct->exit_status = 1;
			return ;
		}
	}
	g_struct->exit_status = 0;
}
