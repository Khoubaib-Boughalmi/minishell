/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:06:47 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/12 16:59:48 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(void)
{
	char	buff[6144];

	if (getcwd(buff, sizeof(buff)))
		ft_printf("%s\n", buff);
	else
		g_struct->exit_status = 1;
	g_struct->exit_status = 0;
}
