/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:18:09 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/09 21:31:33 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand(t_token_lst *tokens_lst)
{
	t_envp_node	*tmp;
	int			i;

	tmp = NULL;
	while (tokens_lst)
	{
		i = -1;
		if (tokens_lst->token->type == AST_COMMAND)
		{
			while (tokens_lst->token->args[++i])
				expand_quotes(&(tokens_lst->token->args[i]));
		}
		else if (tokens_lst->token->type == AST_REDIRECTION)
		{
			if (tokens_lst->token->redirect_fname && \
			tokens_lst->token->red_type != HEREDOC)
				expand_redirection_fname(tokens_lst->token);
		}
		tokens_lst = tokens_lst->next;
	}
}
