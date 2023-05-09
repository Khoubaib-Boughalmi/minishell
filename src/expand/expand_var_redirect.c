/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:31:42 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/09 21:34:11 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*trim_str(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*new_str;

	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	j = ft_strlen(str) - 1;
	while (str[i] && str[i] == ' ')
		i++;
	while (j >= 0 && j >= i && str[j] == ' ')
		j--;
	new_str = (char *)malloc(sizeof(char) * (j - i + 10));
	k = 0;
	while (str[i] && i <= j)
	{
		new_str[k] = str[i];
		i++;
		k++;
	}
	new_str[k] = '\0';
	return (new_str);
}

void	expand_variables_redirect(char **original, char	*copy)
{
	t_envp_node	*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	if (copy[1] == '?')
		expand_exit_status(original, &(copy[1]));
	else if (!copy[1] || copy[1] == ' ' || copy[1] == '|' )
		cbc_str_join(original, '$');
	else
	{
		tmp = envp_find_node(&(copy[1]), get_variable_len(&(copy[1])), \
		g_struct->envp_head);
		if (tmp && tmp->value)
		{
			i = -1;
			while (tmp->value[++i])
				cbc_str_join(original, tmp->value[i]);
		}
	}
}
