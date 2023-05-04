/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:51:44 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/04 20:20:30 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_dquotes_red(char **original, char *copy, int *i)
{
	*i += 1;
	while (copy[*i] && copy[*i] != '\"')
	{
		cbc_str_join(original, copy[*i]);
		*i += 1;
	}
	if (copy[*i] && copy[*i] == '\"')
		*i += 1;
}

void	expand_quotes_red(char **original)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = initiate_origin_copy(original);
	while (copy[i])
	{
		if (copy[i] == '\"')
			expand_dquotes_red(original, copy, &i);
		else if (copy[i] == '\'')
		{
			i++;
			while (copy[i] && copy[i] != '\'')
				cbc_str_join(original, copy[i++]);
			if (copy[i] && copy[i] == '\'')
				i++;
		}
		else
			cbc_str_join(original, copy[i++]);
	}
	free(copy);
}
