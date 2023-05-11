/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:35:43 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/10 19:00:31 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*epur_str_core(char *str, char *new_str, int *i, int *j)
{
	int	flag;

	flag = 0;
	while (str[*i])
	{
		if (str[*i] == ' ' || str[*i] == '\t')
			flag = 1;
		if (!(str[*i] == ' ' || str[*i] == '\t'))
		{
			if (flag)
			{
				new_str[*j] = ' ';
				*j += 1;
			}
			flag = 0;
			new_str[*j] = str[*i];
			*j += 1;
		}
		*i += 1;
	}
	new_str[*j] = '\0';
	return (new_str);
}

char	*epur_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (str);
	while (str[i] == ' ' || str[i] == '\t')
		i += 1;
	epur_str_core(str, new_str, &i, &j);
	return (new_str);
}

int	check_str(char *str)
{
	if (!str || !str[0] || str[0] == '\n')
		return (0);
	return (1);
}
