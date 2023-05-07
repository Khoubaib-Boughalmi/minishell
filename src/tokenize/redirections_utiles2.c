/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utiles2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:23:00 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/05 11:30:25 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_der(char *str)
{
	int		j;
	char	c;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			c = str[j];
			j++;
			while (!str[j] || (str[j] != c && str[j] != c))
				j++;
		}
		if (str[j] == '>' || str[j] == '<')
			return (1);
		j++;
	}
	return (0);
}
