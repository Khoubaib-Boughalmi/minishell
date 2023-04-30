/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:51:44 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/30 19:01:40 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		{
			i++;
			while (copy[i] && copy[i] != '\"')
				cbc_str_join(original, copy[i++]);
			if (copy[i] && copy[i] == '\"')
				i++;
		}
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
