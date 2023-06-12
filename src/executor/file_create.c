/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:20 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 18:17:20 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_in_file_append(char *red)
{
	int	fd;

	if (!red)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		g_struct->exit_status = 1;
		return (-1);
	}
	fd = open(red, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (access(red, W_OK))
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		g_struct->exit_status = 1;
		return (-1);
	}
	if (fd < 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		g_struct->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	redirect_in_file(char *red)
{
	int	fd;

	if (!red)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		g_struct->exit_status = 1;
		return ((-1));
	}
	fd = open(red, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (access(red, W_OK))
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		g_struct->exit_status = 1;
		return (-1);
	}
	if (fd < 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		g_struct->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	redirect_out_file(char *red)
{
	int	fd;

	fd = open(red, O_RDWR);
	if (access(red, F_OK))
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		g_struct->exit_status = 1;
		return (-1);
	}
	if (access(red, R_OK))
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		g_struct->exit_status = 1;
		return (-1);
	}
	return (fd);
}
