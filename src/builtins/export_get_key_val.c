/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_key_val.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:41:39 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/09 21:09:49 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_key(char *str)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	len = 0;
	key = NULL;
	while (str[len] && str[len] != '=')
		len++;
	if (len)
	{
		key = (char *)malloc(sizeof(char) * (len + 1));
		if (!key)
			return (NULL);
		while (str[i] && str[i] != '=')
		{
			key[i] = str[i];
			i++;
		}
		key[i] = '\0';
	}
	return (key);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	if (str[i])
	{
		value = (char *)malloc(sizeof(char) * (ft_strlen(&str[i]) + 1));
		if (!value)
			return (NULL);
		while (str[i])
			value[j++] = str[i++];
		value[j] = '\0';
	}
	else
	{
		value = (char *)malloc(sizeof(char));
		value[0] = '\0';
	}
	return (value);
}
