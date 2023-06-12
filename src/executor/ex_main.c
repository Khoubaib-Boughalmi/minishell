/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:40:30 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 18:16:11 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ex_main_norm2(t_redirection **list_reds, char **str)
{
	if (redirect_in_out(list_reds))
		exit(g_struct->exit_status);
	if (is_builtin(str[0]))
	{
		handle_builtin(str);
		exit(g_struct->exit_status);
	}
}

void	ex_main_norm(t_redirection **list_reds, char **str)
{
	ex_main_norm2(list_reds, str);
	if (str[0][0] && path_finder(str[0], g_struct->envp_head))
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
	else if (str && !list_reds[0])
		cmd_not_found(str);
	free_cmds_reds_array(str, list_reds);
	exit (0);
}

void	ex_main(t_token_lst *token1, t_token_lst *token2)
{
	int				fd[2];
	char			**str;
	t_redirection	**list_reds;
	int				a1;

	pipe(fd);
	g_struct->stout = dup2(fd[1], 1);
	close(fd[1]);
	str = create_lst_commands(token1);
	list_reds = create_lst_redirections(token1);
	signal(SIGINT, SIG_IGN);
	a1 = fork();
	if (a1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		ex_main_norm(list_reds, str);
	}
	free_cmds_reds_array(str, list_reds);
	g_struct->stin = dup2(fd[0], 0);
	close(fd[0]);
	executor(token2);
	signal(SIGINT, &sigint_hander_executor);
}
