/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:09:51 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 18:17:31 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_in_out_norm(t_redirection **list_reds, int i, int	*fd)
{
	if (list_reds[i]->type == OUTPUT)
	{
		fd[i] = redirect_in_file(list_reds[i]->value);
		if (fd[i] < 0)
			return (1);
	}
	if (list_reds[i]->type == APPEND)
	{
		fd[i] = redirect_in_file_append(list_reds[i]->value);
		if (fd[i] < 0)
			return (1);
	}
	if (list_reds[i]->type == INPUT)
	{
		fd[i] = redirect_out_file(list_reds[i]->value);
		if (fd[i] < 0)
			return (1);
	}
	return (0);
}

int	ambiguous_check(t_redirection **list_reds, int i)
{
	if (list_reds[i]->redirect_error == AMBIGUOUSERR)
	{
		ft_putstr_fd("minishell : ambiguous redirect\n", 2);
		g_struct->exit_status = 1;
		return (1);
	}
	else if (list_reds[i]->redirect_error == FILEERR)
	{
		ft_putstr_fd("minishell : No such file or directory\n", 2);
		g_struct->exit_status = 1;
		return (1);
	}
	return (0);
}

int	heredoc_norm(t_redirection **list_reds, int *fd)
{
	int	i;

	i = 0;
	while (list_reds[i])
	{
		if (list_reds[i]->type == HEREDOC)
		{
			fd[i] = redirect_out_file_heredoc(list_reds[i]->value);
			if (fd[i] < 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	redirect_in_out(t_redirection **list_reds)
{
	int	i;
	int	*fd;

	i = 0;
	fd = malloc(splcount(list_reds) * sizeof(int));
	if (heredoc_norm(list_reds, fd))
		return (1);
	while (list_reds[i])
	{
		if (ambiguous_check(list_reds, i))
		{
			free(fd);
			return (1);
		}
		if (redirect_in_out_norm(list_reds, i, fd))
		{
			free(fd);
			return (1);
		}
		i++;
	}
	red_in_last(list_reds, fd);
	red_out_last(list_reds, fd);
	free(fd);
	return (0);
}

void	cmd_not_found(char **cmd)
{
	dup2(g_struct->ppout, 1);
	ft_putstr_fd("minishell : command not found\n", 2);
	free_split(cmd);
	g_struct->exit_status = 127;
	exit (g_struct->exit_status);
}
