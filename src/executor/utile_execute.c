/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:01:59 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/05 11:08:24 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	red_in_last(t_redirection **list_reds, int *fd)
{
	int	i;
	int	t;

	i = 0;
	t = -1;
	while (list_reds[i])
	{
		if (list_reds[i]->type == OUTPUT)
			t = fd[i];
		if (list_reds[i]->type == APPEND)
			t = fd[i];
		i++;
	}
	if (t != -1)
		dup2(t, 1);
}

void	red_out_last(t_redirection **list_reds, int *fd)
{
	int	i;
	int	t;

	i = 0;
	t = -1;
	while (list_reds[i])
	{
		if (list_reds[i]->type == INPUT)
			t = fd[i];
		if (list_reds[i]->type == HEREDOC)
			t = fd[i];
		i++;
	}
	if (t != -1)
		dup2(t, 0);
}

int	splcount(t_redirection **list_reds)
{
	int	count;

	count = 0;
	while (list_reds[count])
		count++;
	return (count);
}
