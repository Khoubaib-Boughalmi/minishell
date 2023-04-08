/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utiles1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:23:05 by rennatiq          #+#    #+#             */
/*   Updated: 2023/04/07 21:26:26 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_der_left(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '<')
			return (1);
		j++;
	}
	return (0);
}

int	ft_check_der_right(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '>')
			return (1);
		j++;
	}
	return (0);
}

int	ft_check_last_der2(char	*input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '\0')
		{
			j = i + 1;
			while (input[j] != '\0')
			{
				if (input[i] != ' ' && input[i] != '\t')
					break ;
				j++;
			}
			if (input[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_cout_red(char *input, char c)
{
	int		count;
	int		i;
	char	n;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			n = input[i];
			i++;
			while (!input[i] || (input[i] != n && input[i] != n))
				i++;
		}
		if (input[i] == c && (input[i + 1] != c || input[i + 1] != '\0'))
			count++;
		i++;
	}
	return (count);
}
