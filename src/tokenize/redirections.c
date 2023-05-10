/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:13:46 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 21:30:34 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_der_exe(char	*str, char n)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == n)
			return (1);
		i++;
	}
	return (0);
}

void	split_norm(char **res, char *str, int *j)
{
	int		k;
	char	**temp;

	k = 0;
	temp = ft_split_qotes(str, '>');
	temp = ft_der_insert_2(str, temp, ">>", ">");
	while (temp[k])
	{
		res[*j] = ft_strdup(temp[k++]);
		(*j)++;
	}
	free_split(temp);
}

void	split_norm2(char **res, char *str, int *j)
{
	int		k;
	char	**temp;

	k = 0;
	temp = ft_split_qotes(str, '<');
	temp = ft_der_insert_2(str, temp, "<<", "<");
	while (temp[k])
	{
		res[*j] = ft_strdup(temp[k++]);
		(*j)++;
	}
	free_split(temp);
}

char	**ft_split_der(char	**str, char n)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = malloc((ft_count_str(str) + ft_count_der(str, n) + 1)
			* sizeof(char *));
	while (str[i])
	{
		if (n == '>' && if_der_exe(str[i], n))
			split_norm(res, str[i], &j);
		else if (n == '<' && if_der_exe(str[i], n))
			split_norm2(res, str[i], &j);
		else
			res[j++] = ft_strdup(str[i]);
		i++;
	}
	res[j] = 0;
	free_split(str);
	return (res);
}
