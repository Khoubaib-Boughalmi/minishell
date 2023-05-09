/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:04:58 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 18:12:52 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	transforming_token_lst(t_token_lst *token_lst)
{
	printf("num_cmd %d\n", count_commands(token_lst));
	printf("num_red %d\n", count_redirections(token_lst));
}

char	**create_lst_commands(t_token_lst *token_lst)
{
	int		i;
	int		j;
	char	**lst_cmd;

	j = -1;
	lst_cmd = (char **)malloc(sizeof(char *)
			* (count_commands(token_lst) + 2));
	if (!lst_cmd)
		return (0);
	while (token_lst && token_lst->token->type != AST_PIPE)
	{
		i = -1;
		if (token_lst->token->type == AST_COMMAND)
		{
			while (++i < token_lst->token->num_args)
			{
				if (token_lst->token->args[i] == NULL)
					continue;
				lst_cmd[++j] = token_lst->token->args[i];
			}
		}
		token_lst = token_lst->next;
	}
	lst_cmd[j + 1] = 0;
	return (lst_cmd);
}

t_redirection	**create_lst_redirections(t_token_lst *token_lst)
{
	t_redirection	**lst_reds;
	int				i;

	i = -1;
	lst_reds = (t_redirection **)malloc(sizeof(t_redirection *)
			* (count_redirections(token_lst) + 1));
	if (!lst_reds)
		return (0);
	while (token_lst && token_lst->token->type != AST_PIPE)
	{
		if (token_lst->token->type == AST_REDIRECTION)
		{
			lst_reds[++i] = (t_redirection *)malloc(sizeof(t_redirection));
			if (!lst_reds[i])
			{
				free(lst_reds);
				return (0);
			}
			lst_reds[i]->value = token_lst->token->redirect_fname;
			lst_reds[i]->type = token_lst->token->red_type;
			lst_reds[i]->redirect_error = token_lst->token->redirect_error;
		}
		token_lst = token_lst->next;
	}
	lst_reds[i + 1] = 0;
	return (lst_reds);
}
