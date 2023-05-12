/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:28:10 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 15:27:17 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_access_norm(char **str)
{
	if (access(path_finder(str[0], g_struct->envp_head), F_OK) < 0)
	{
		ft_printf("minishell: No such file or directory\n");
		exit(127);
	}
	if (access(path_finder(str[0], g_struct->envp_head), X_OK) < 0)
	{
		ft_printf("minishell: %s: Permission denied\n", str[0]);
		exit(126);
	}
}

void	execut_token_norm(char **str, t_redirection **list_reds)
{
	int	a1;

	signal(SIGINT, SIG_IGN);
	a1 = fork();
	if (a1 == 0)
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

void	execut_token(t_token_lst	*tokens_lst)
{
	char			**str;
	t_redirection	**list_reds;

	str = create_lst_commands(tokens_lst);
	list_reds = create_lst_redirections(tokens_lst);
	if (is_builtin2(str[0]))
	{
		if (redirect_in_out(list_reds))
			exit(g_struct->exit_status);
		handle_builtin(str);
		dup2(g_struct->ppout, 1);
		dup2(g_struct->ppin, 0);
	}
	else
	{
		execut_token_norm(str, list_reds);
		g_struct->exit_status = (g_struct->exit_status >> 8) & 255;
	}
	free_cmds_reds_array(str, list_reds);
}

int	tokenize_expand_execute_norm(char *input, t_token_lst *tokens_lst)
{
	if (ft_check_mul_pipe(input, tokens_lst))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		free_token_lst(tokens_lst);
		g_struct->exit_status = 2;
		return (1);
	}
	g_struct->tokens_head = tokens_lst;
	expand(tokens_lst);
	g_struct->ppin = dup(0);
	g_struct->ppout = dup(1);
	return (0);
}

int	tokenize_expand_execute(char *input)
{
	t_token_lst	*tokens_lst;

	if (syntax_errors(input))
	{
		g_struct->exit_status = 2;
		return (1);
	}
	tokens_lst = tokenize(input);
	if (!tokens_lst)
		return (1);
	if (tokenize_expand_execute_norm(input, tokens_lst))
		return (1);
	if (is_pipe(tokens_lst))
		executor(tokens_lst);
	else
		execut_token(tokens_lst);
	free_token_lst(tokens_lst);
	return (1);
}
