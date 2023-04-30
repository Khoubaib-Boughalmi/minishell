/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:55:03 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/29 15:03:04 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_flags(char	*flag)
{
	int	i;

	i = 1;
	if (flag[0] != '-')
		return (0);
	while (flag[i] && flag[i] == 'n')
		i++;
	if (!flag[i])
		return (1);
	return (0);
}

void	ft_echo_core(char **list_vars, int flag)
{
	int	i;

	i = 0;
	while (check_flags(list_vars[++i]))
		flag = 1;
	if (!flag)
	{
		while (list_vars[i])
		{
			if (list_vars[i + 1])
				ft_printf("%s ", list_vars[i++]);
			else
				ft_printf("%s\n", list_vars[i++]);
		}
	}
	else
	{
		while (list_vars[i])
		{
			if (list_vars[i + 1])
				ft_printf("%s ", list_vars[i++]);
			else
				ft_printf("%s", list_vars[i++]);
		}
	}
}

void	ft_echo(char	**list_vars)
{
	int	flag;

	flag = 0;
	if (!check_str(list_vars[1]))
		ft_printf("\n");
	else
		ft_echo_core(list_vars, flag);
	g_struct->exit_status = 0;
}
