/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:28:10 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 17:30:16 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
