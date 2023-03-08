/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:33:14 by kboughal          #+#    #+#             */
/*   Updated: 2022/10/23 18:33:14 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_get_sticky(int fd, char *sticky);
char	*ft_remove_excess(char *str);
char	*ft_get_new_sticky(char *str);

int		ft_new_line(char *str);
int		ft_get_pos(char *str);

size_t	ft_strlen_gnl(char *str);

#endif