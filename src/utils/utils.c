/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:48:55 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/14 17:05:46 by kboughal         ###   ########.fr       */
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

int	check_str(char *str)
{
	if (!str || !str[0] || str[0] == '\n')
		return (0);
	return (1);
}

char	*create_envp_value(char *key)
{
	char		*full_path;
	t_envp_node	*envp_ptr;

	envp_ptr = g_struct->envp_head;
	full_path = NULL;
	while (envp_ptr)
	{
		if (!strncmp(key, envp_ptr->key, 4))
		{
			full_path = (char *)malloc(sizeof(char) * \
			ft_strlen(envp_ptr->value) + 1);
			ft_strlcpy(full_path, envp_ptr->value, \
			ft_strlen(envp_ptr->value) + 1);
			break ;
		}
		envp_ptr = envp_ptr->next;
	}
	return (full_path);
}

char	*epur_str(char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*new_str;

	flag = (i = 0, j = 0, 0);
	new_str = (char *)malloc(sizeof(char) * ft_strlen(str + 1));
	if (!new_str)
		return (str);
	while (str[i] == ' ' || str[i] == '\t')
		i += 1;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			flag = 1;
		if (!(str[i] == ' ' || str[i] == '\t'))
		{
			if (flag)
			{
				new_str[j] = ' ';
				j++;
			}
			flag = 0;
			new_str[j] = str[i];
			j++;
		}
		i += 1;
	}
	new_str[j] = '\0';
	return (new_str);
}
