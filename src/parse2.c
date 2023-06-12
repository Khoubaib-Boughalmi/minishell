/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:25:11 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/12 18:13:17 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_access_norm(char **str)
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
}

void	execut_token_norm2(char **str, t_redirection **list_reds)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (redirect_in_out(list_reds))
		exit(g_struct->exit_status);
	if (is_builtin(str[0]))
	{
		handle_builtin(str);
		exit(g_struct->exit_status);
	}
}

void	execut_token_norm(char **str, t_redirection **list_reds)
{
	int	a1;

	signal(SIGINT, SIG_IGN);
	a1 = fork();
	if (a1 == 0)
	{
		execut_token_norm2(str, list_reds);
		if (str[0][0] && path_finder(str[0], g_struct->envp_head))
		{
			check_access_norm(str);
			execve(path_finder(str[0], g_struct->envp_head),
				str, get_envp_arr());
		}
		else if (str[0] && !list_reds[0])
			cmd_not_found(str);
		exit (0);
	}
	waitpid(a1, &g_struct->exit_status, 0);
	signal(SIGINT, &sigint_hander);
}
