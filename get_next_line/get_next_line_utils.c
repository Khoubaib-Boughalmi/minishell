/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:43:57 by kboughal          #+#    #+#             */
/*   Updated: 2022/10/23 16:43:57 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*str;
	int			i;
	int			j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1 && s1[++i] != '\0')
		str[i] = s1[i];
	j = 0;
	while (s2 && s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_new_sticky(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = ft_get_pos(str);
	j = 0;
	new_str = NULL;
	if (!i)
		return (NULL);
	if (str[i])
	{
		new_str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(&str[i]) + 1));
		if (!new_str)
		{
			free(str);
			return (NULL);
		}
		while (str[i] != '\0')
			new_str[j++] = str[i++];
		new_str[j] = '\0';
	}
	free(str);
	return (new_str);
}

int	ft_get_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	i++;
	return (i);
}
