/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:38:24 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 21:36:19 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor_norm(char **str, t_redirection **list_reds, t_token_lst *tmp1)
{
	dup2(g_struct->ppout, 1);
	str = create_lst_commands(tmp1);
	list_reds = create_lst_redirections(tmp1);
	signal(SIGINT, &sigint_hander_executor);
	last_cmd_norm(list_reds, str);
	free_cmds_reds_array(str, list_reds);
	dup2(g_struct->ppout, 1);
	dup2(g_struct->ppin, 0);
}

void	executor(t_token_lst *token_lst)
{
	char			**str;
	t_redirection	**list_reds;
	int				i;
	t_token_lst		*tmp1;

	i = -1;
	str = NULL;
	list_reds = NULL;
	if (!token_lst)
		return ;
	tmp1 = token_lst;
	while (token_lst)
	{
		if (token_lst->token->type == AST_PIPE)
		{
			if (!token_lst->next)
				return ;
			token_lst = token_lst->next;
			ex_main(tmp1, token_lst);
			return ;
		}
		token_lst = token_lst->next;
	}
	executor_norm(str, list_reds, tmp1);
}
