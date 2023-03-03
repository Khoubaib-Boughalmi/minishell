/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:42:19 by kboughal          #+#    #+#             */
/*   Updated: 2022/10/23 16:42:19 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_sticky(int fd, char *sticky)
{
	char	*buf;
	int		read_bytes;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!ft_new_line(sticky) && read_bytes)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		sticky = ft_strjoin_gnl(sticky, buf);
	}
	if (!sticky && !read_bytes)
		return (NULL);
	free(buf);
	return (sticky);
}

char	*ft_remove_excess(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char			*sticky;
	char				*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	sticky = ft_get_sticky(fd, sticky);
	if (!sticky)
		return (NULL);
	line = ft_remove_excess(sticky);
	sticky = ft_get_new_sticky(sticky);
	return (line);
}
