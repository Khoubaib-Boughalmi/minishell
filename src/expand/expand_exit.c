/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:50:44 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/30 18:51:26 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_exit_status(char **original, char *copy)
{
	char	*expanded_exit;
	char	*itoa_str;
	int		i;

	i = -1;
	if (WIFEXITED(g_struct->exit_status))
		g_struct->exit_status = WEXITSTATUS(g_struct->exit_status);
	if (ft_strlen(copy) >= 2)
	{
		itoa_str = ft_itoa(g_struct->exit_status);
		expanded_exit = ft_strjoin(itoa_str, &(copy[1]));
		while (expanded_exit[++i] && i <= get_variable_len(&(copy[1])))
			cbc_str_join(original, expanded_exit[i]);
		free(itoa_str);
	}
	else
	{
		expanded_exit = ft_itoa(g_struct->exit_status);
		while (expanded_exit[++i])
			cbc_str_join(original, expanded_exit[i]);
	}
	free(expanded_exit);
}
