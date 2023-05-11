/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:48:55 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/10 19:00:27 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}

void	free_args(t_token_lst *current, char **list)
{
	int	i;

	i = -1;
	while (++i < current->token->num_args)
		free(list[i]);
	free(list);
}

int	is_part_of_list(char c, char *list)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(list))
	{
		if (list[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	two_d_array_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	ft_strlcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (0);
	i = 0;
	l1 = get_variable_len((char *)s1);
	l2 = get_variable_len((char *)s2);
	if (l1 != l2)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
