/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection_vars.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:07:27 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/09 21:34:20 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_chars(char	*copy, int *i)
{
	while (copy[*i] && copy[*i] != ' ' && copy[*i] != '\"' \
	&& copy[*i] != '\'' && copy[*i] != '$' && copy[*i] != '|' \
	&& copy[*i] != '-')
		*i += 1;
}

void	expand_no_quotes_red(char **original, char *copy, int *i, int *vars)
{
	if (copy[*i] == '$' && (ft_isdigit(copy[*i + 1]) || copy[*i + 1] == '@'))
		*i += 2;
	else if (copy[*i] == '$')
	{
		*vars = 1;
		expand_variables_redirect(original, copy + *i);
		*i += 1;
		skip_chars(copy, i);
	}
	else
	{
		cbc_str_join(original, copy[*i]);
		*i += 1;
	}
}

void	expand_squotes(char **original, char *copy, int *i)
{
	*i += 1;
	while (copy[*i] && copy[*i] != '\'')
	{
		cbc_str_join(original, copy[*i]);
		*i += 1;
	}
	if (copy[*i] == '\'')
		*i += 1;
}

void	expand_dquotes(char **original, char *copy, int *i, int *vars)
{
	cbc_str_join(original, copy[*i]);
	*i += 1;
	while (copy[*i] && copy[*i] != '\"')
	{
		if (copy[*i] == '$' && ft_isdigit(copy[*i + 1]))
			i += 2;
		else if (copy[*i] == '$')
		{
			*vars = 1;
			expand_variables_redirect(original, copy + *i);
			*i += 1;
			skip_chars(copy, i);
		}
		else
		{
			cbc_str_join(original, copy[*i]);
			*i += 1;
		}
	}
	if (copy[*i] == '\"')
	{
		cbc_str_join(original, copy[*i]);
		*i += 1;
	}
}

int	expand_redirection_vars(char **original, char *copy)
{
	int	i;
	int	vars;

	i = 0;
	vars = 0;
	while (copy[i])
	{
		if (copy[i] == '\'')
			expand_squotes(original, copy, &i);
		else if (copy[i] == '\"')
			expand_dquotes(original, copy, &i, &vars);
		else
			expand_no_quotes_red(original, copy, &i, &vars);
	}
	return (check_ambiguous(vars, original));
}
