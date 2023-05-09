/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:57:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/09 18:20:53 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_variable_len(char *start)
{
	size_t	i;

	i = 0;
	while (start[i] && start[i] != ' ' && start[i] != '\"' && \
	start[i] != '\'' && start[i] != '$' && start[i] != '|' && start[i] != '-')
		i++;
	return (i);
}

char	*initiate_origin_copy(char **original)
{
	char	*copy;

	copy = (char *)malloc(sizeof(char) * ft_strlen(*original) + 1);
	ft_strlcpy(copy, *original, ft_strlen(*original) + 1);
	copy[ft_strlen(*original)] = '\0';
	memset(*original, 0, ft_strlen(*original));
	free(*original);
	*original = NULL;
	return (copy);
}

void	set_ambiguous_state(t_token *token)
{
	token->redirect_error = AMBIGUOUSERR;
	g_struct->exit_status = 1;
}

int	get_start(char *str)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str && str[i])
	{
		if (str[i] && (str[i] != '\"' && str[i] != '\''))
			return (start);
		if (str[i + 1] && (str[i] == '\"' || str[i] == '\'') \
		&& str[i + 1] == str[i])
			start = i + 2;
		i += 1;
	}
	return (start);
}
