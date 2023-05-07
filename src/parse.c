/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:28:10 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/07 10:00:26 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe(t_token_lst *tokens_lst)
{
	t_token_lst	*tmp;

	tmp = tokens_lst;
	while (tmp)
	{
		if (tmp->token->type == AST_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

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

	signal(SIGINT, &sigint_hander_executor);
	a1 = fork();
	if (a1 == 0)
	{
		if (redirect_in_out(list_reds))
			exit(g_struct->exit_status);
		if (is_builtin(str[0]))
		{
			handle_builtin(str);
			exit(g_struct->exit_status);
		}
		else if (str[0] && path_finder(str[0], g_struct->envp_head))
		{
			check_access_norm(str);
			signal(SIGQUIT, SIG_DFL);
			execve(path_finder(str[0], g_struct->envp_head),
				str, get_envp_arr());
		}
		else if (str && !list_reds[0])
			cmd_not_found(str);
		exit (0);
	}
	waitpid(a1, &g_struct->exit_status, 0);
}

void	execut_token(t_token_lst	*tokens_lst)
{
	char			**str;
	t_redirection	**list_reds;

	str = create_lst_commands(tokens_lst);
	list_reds = create_lst_redirections(tokens_lst);
	if (is_builtin2(str[0]))
		handle_builtin(str);
	else
	{
		execut_token_norm(str, list_reds);
		if (WIFEXITED(g_struct->exit_status))
			g_struct->exit_status = WEXITSTATUS(g_struct->exit_status);
		else if (WIFSIGNALED(g_struct->exit_status))
			g_struct->exit_status = WTERMSIG(g_struct->exit_status) + 127;
	}
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
	if (ft_check_mul_pipe(input, tokens_lst))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_struct->exit_status = 2;
		return (1);
	}
	g_struct->tokens_head = tokens_lst;
	expand(tokens_lst);
	g_struct->ppin = dup(0);
	g_struct->ppout = dup(1);
	if (is_pipe(tokens_lst))
		executor(tokens_lst);
	else
		execut_token(tokens_lst);
	return (1);
}
