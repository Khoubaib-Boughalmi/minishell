/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:03:55 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/12 18:15:41 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit_core(char **list_vars)
{
	int	i;

	i = 0;
	if (!list_vars[1][0])
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(255);
	}
	if (list_vars[1][0] == '-')
		i++;
	while (list_vars[1][i])
	{
		if (!ft_isdigit(list_vars[1][i]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
}

void	ft_exit(char **list_vars)
{
	long long	ex_status;

	if (list_vars[1])
		ft_exit_core(list_vars);
	if (list_vars_len(list_vars) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_struct->exit_status = 1;
	}
	else if (list_vars_len(list_vars) == 2)
	{
		ex_status = ft_atoi(list_vars[1]);
		g_struct->exit_status = ex_status & 255;
		exit(g_struct->exit_status);
	}
	else
		exit(g_struct->exit_status);
}
