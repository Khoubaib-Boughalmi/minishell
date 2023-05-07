/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:07:39 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/05 11:44:22 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_qoutes(char *input)
{
	int		i;
	char	n;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			n = input[i];
			i++;
			while (!input[i] || input[i] != n)
			{
				i++;
				if (!input[i])
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_check_pipes(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '|')
			break ;
		if (input[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	syntax_errors(char *input)
{
	if (ft_check_qoutes(input))
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching\n",
			2);
		return (1);
	}
	if (ft_check_mul_der(input, '>') || ft_check_mul_der(input, '<'))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (1);
	}
	if (ft_check_pipes(input))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (1);
	}
	return (0);
}
