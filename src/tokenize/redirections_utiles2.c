/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utiles2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:23:00 by rennatiq          #+#    #+#             */
/*   Updated: 2023/04/07 21:23:01 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_dub_der2(char	*input, char n)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == n && input[i + 1] == n)
			return (1);
		i++;
	}
	return (0);
}

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
