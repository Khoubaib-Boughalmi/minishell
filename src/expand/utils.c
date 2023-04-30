/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:57:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/30 18:58:56 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_variable_len(char *start)
{
	size_t	i;

	i = 0;
	while (start[i] && start[i] != ' ' && start[i] != '\"' && start[i] != '\'' && start[i] != '$' && start[i] != '|'  && start[i] != '-')
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