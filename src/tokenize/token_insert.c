/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:03:21 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 21:31:07 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_insert(t_token_lst	*node, char *str)
{
	node->token->args = ft_split(str, ' ');
	node->token->type = AST_PIPE;
	node->token->num_args = 0;
	node->token->redirect_fd = NULL;
	node->token->redirect_fname = NULL;
}

void	cmd_insert(t_token_lst	*node, char *str)
{
	int	j;

	j = 0;
	node->token->args = ft_split_qotes(str, ' ');
	while (node->token->args[j])
		j++;
	node->token->num_args = j;
	node->token->redirect_fd = NULL;
	node->token->redirect_fname = NULL;
	node->token->type = AST_COMMAND;
}

void	rediractions_insert2(t_token_lst *node2, t_token_lst *node, char **tmp)
{
	int	k;

	if (tmp[1])
	{
		k = 1;
		node2 = malloc(sizeof(t_token_lst));
		node2->token = malloc(sizeof(t_token));
		node2->next = NULL;
		while (tmp[k])
			k++;
		node2->token->args = malloc((k) * sizeof(char *));
		k = 1;
		while (tmp[k])
		{
			node2->token->args[k - 1] = ft_strdup(tmp[k]);
			k++;
		}
		node2->token->args[k - 1] = 0;
		node2->token->num_args = k - 1;
		node2->token->redirect_fd = NULL;
		node2->token->redirect_fname = NULL;
		node2->token->type = AST_COMMAND;
		node->next = node2;
	}
}

void	rediractions_insert(t_token_lst	*node, char *str1, char *str2, int *i)
{
	char		**tmp;
	t_token_lst	*node2;

	node2 = NULL;
	node->token->red_type = redtype(str1);
	node->token->redirect_fd = ft_strdup(str1);
	node->token->args = NULL;
	node->token->num_args = 0;
	node->token->type = AST_REDIRECTION;
	if (!str2 || ft_check_der(str2) || ft_check_pipe(str2))
		node->token->redirect_fname = NULL;
	else
	{
		tmp = ft_split_qotes(str2, ' ');
		if (!tmp[0])
			node->token->redirect_fname = NULL;
		else
		{
			node->token->redirect_fname = ft_strdup(tmp[0]);
			rediractions_insert2(node2, node, tmp);
		}
		free_split(tmp);
		(*i)++;
	}
}

t_token_lst	*ft_put_intoken(char **str)
{
	t_token_lst	*node;
	t_token_lst	*token;
	int			i;

	i = 0;
	token = NULL;
	node = NULL;
	while (i < ft_count_str(str))
	{
		node = malloc(sizeof(t_token_lst));
		node->token = malloc(sizeof(t_token));
		node->next = NULL;
		if (ft_check_pipe(str[i]))
			pipe_insert(node, str[i]);
		else if (ft_check_der(str[i]))
			rediractions_insert(node, str[i], str[i + 1], &i);
		else
			cmd_insert(node, str[i]);
		ft_lst_token_add_back(&token, node);
		i++;
	}
	free_split(str);
	return (token);
}
