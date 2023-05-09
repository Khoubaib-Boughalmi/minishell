/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_der.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:31:59 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 21:26:34 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	qoutes_sciper(char	*input, int i)
{
	char	n;

	if (!input[i] && (input[i] == '\'' || input[i] == '\"'))
	{
		n = input[i];
		i++;
		while (!input[i] || (input[i] != n && input[i] != n))
			i++;
	}
	return (i);
}

int	ft_check_mul_der_norm(char	*input, char c, int k, int i)
{
	int		j;

	j = i;
	while (input[j])
	{
		if (input[j++] == c)
			k++;
		else
			break ;
	}
	return (k);
}

int	ft_check_mul_der(char	*input, char c)
{
	int		i;
	int		k;

	i = 0;
	while (input[i])
	{
		k = 0;
		i = qoutes_sciper(input, i);
		if (!input[i])
			return (1);
		if (input[i] == c)
			k = ft_check_mul_der_norm(input, c, k, i);
		if (k > 2)
			return (1);
		i++;
	}
	return (0);
}
