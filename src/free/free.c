/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:13:46 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/10 19:14:07 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_list_reds(t_redirection **list_reds)
{
	int	i;

	i = 0;
	while (list_reds[i])
	{
		if (list_reds[i]->value)
			free(list_reds[i]->value);
		free(list_reds[i]);
		i++;
	}
	free(list_reds);
}

void	free_cmds_reds_array(char **list_cmds, t_redirection **list_reds)
{
	int	i;

	i = -1;
	if (list_cmds)
		free_split(list_cmds);
	if (list_reds)
		free_list_reds(list_reds);
}
