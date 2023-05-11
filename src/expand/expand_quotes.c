/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:26:18 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/11 18:18:52 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_double_quotes(char **original, int *i, char *copy)
{
	*i += 1;
	while (copy[*i] && copy[*i] != '\"')
	{
		if (copy[*i] == '$' && ft_isdigit(copy[*i + 1]))
			*i += 2;
		else if (copy[*i] == '$')
		{
			expand_variables(original, copy + *i, NOTRIM);
			*i += 1;
			while (copy[*i] && copy[*i] != ' ' && copy[*i] != '\"' \
			&& copy[*i] != '\'' && copy[*i] != '$' && copy[*i] != '|' \
			&& copy[*i] != '-')
				*i += 1;
		}
		else if (copy[*i] != '$')
		{
			cbc_str_join(original, copy[*i]);
			*i += 1;
		}
	}
	if (copy[*i] == '\"')
		*i += 1;
}

void	expand_no_quotes(char **original, int *i, char *copy)
{
	if (copy[*i] == '$' && (ft_isdigit(copy[*i + 1]) || copy[*i + 1] == '@'))
		*i += 2;
	else if (copy[*i] == '$')
	{
		if (*i)
			expand_variables(original, copy + *i, NOTRIM);
		else
			expand_variables(original, copy + *i, TRIM);
		*i += 1;
		while (copy[*i] && copy[*i] != ' ' && copy[*i] != '\"' \
		&& copy[*i] != '\'' && copy[*i] != '$' && copy[*i] != '-')
			*i += 1;
	}
	else
	{
		cbc_str_join(original, copy[*i]);
		*i += 1;
	}
}

void	expand_quotes(char **original)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = initiate_origin_copy(original);
	if(!ft_strlcmp(copy, "\"\"") || !ft_strlcmp(copy, "\'\'"))
	{
		// ft_printf("sdasdasd\n");
		cbc_str_join(original, '\0');
	}
	else
	{
		while (copy[i])
		{
			if (copy[i] == '\"')
				expand_double_quotes(original, &i, copy);
			else if (copy[i] == '\'')
			{
				i++;
				while (copy[i] && copy[i] != '\'')
					cbc_str_join(original, copy[i++]);
				if (copy[i] == '\'')
					i++;
			}
			else
				expand_no_quotes(original, &i, copy);
		}
	}
	free(copy);
}
