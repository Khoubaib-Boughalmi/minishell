/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:26:32 by rennatiq          #+#    #+#             */
/*   Updated: 2023/04/08 00:27:44 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_der_insert_2(char	*input, char	**str, char *c, char *a)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		m;
	char	n;

	i = 0;
	j = 0;
	k = 0;
	res = malloc((ft_count_str(str) + ft_cout_red(input, c[0]) + 3)
			* sizeof(char *));
	while (input[k] == ' ')
			k++;
	if (input[k] == c[0])
	{
		k++;
		if (input[k] == c[0])
		{
			k++;
			res[j] = ft_strdup(c);
		}
		else
			res[j] = ft_strdup(a);
		j++;
	}
	while (str[i])
	{
		res[j++] = ft_strdup(str[i]);
		while (input[k])
		{
			if (input[k] == '\'' || input[k] == '\"')
			{
				n = input[k++];
				while (!input[k] || input[k] != n)
					k++;
			}
			if (input[k] == c[0])
			{
				k++;
				if (input[k] == c[0])
				{
					k++;
					res[j++] = ft_strdup(c);
					break ;
				}
				res[j++] = ft_strdup(a);
				break ;
			}
			k++;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}
