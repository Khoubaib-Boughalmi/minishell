/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:06:10 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 18:16:30 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execve_norm(char **str)
{
	if (access(path_finder(str[0], g_struct->envp_head), F_OK) < 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		exit(127);
	}
	if (access(path_finder(str[0], g_struct->envp_head), X_OK) < 0)
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		exit(126);
	}
	execve(path_finder(str[0], g_struct->envp_head),
		str, get_envp_arr());
}

void	last_cmd_norm2(void)
{
	g_struct->exit_status = (g_struct->exit_status >> 8) & 255;
	close(g_struct->stin);
	close(g_struct->stout);
	while (wait(NULL) > 0)
		;
	signal(SIGINT, &sigint_hander);
}

void	last_cmd_norm(t_redirection **list_reds, char **str)
{
	int	a1;

	signal(SIGINT, SIG_IGN);
	a1 = fork();
	if (a1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (redirect_in_out(list_reds))
			exit(g_struct->exit_status);
		if (is_builtin(str[0]))
		{
			handle_builtin(str);
			exit(g_struct->exit_status);
		}
		if (str[0][0] && path_finder(str[0], g_struct->envp_head))
			execve_norm(str);
		else if (str && !list_reds[0])
			cmd_not_found(str);
		exit (0);
	}
	waitpid(a1, &g_struct->exit_status, 0);
	last_cmd_norm2();
}
