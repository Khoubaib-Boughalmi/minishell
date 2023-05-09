/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_dub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:32:55 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 21:26:47 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_init(t_token_lst *tokens_lst)
{
	t_token_lst	*tmp;

	tmp = tokens_lst;
	if (tmp->token->type == AST_PIPE)
		return (1);
	while (tmp)
	{
		if (tmp->token->type == AST_REDIRECTION)
		{
			if (tmp->token->redirect_fname == NULL)
				return (1);
		}
		if (tmp->token->type == AST_PIPE)
		{
			if (tmp->next == NULL)
				return (1);
		}
		if (tmp->token->type == AST_COMMAND)
		{
			if (tmp->token->args[0] == NULL)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_init2(char	*input, int i)
{
	int	j;

	if (input[i] == '|')
	{
		j = i + 1;
		while (input[j] == ' ')
			j++;
		while (input[j])
		{
			if (input[j] == '|')
				return (1);
			else
				break ;
			j++;
		}
	}
	return (0);
}

int	ft_check_init3(char	*input, int i)
{
	char	n;

	if (input[i] == '\0' && (input[i] == '\'' || input[i] == '\"'))
	{
		n = input[i];
		i++;
		while (!input[i] || (input[i] != n && input[i] != n))
			i++;
	}
	return (i);
}

int	ft_check_mul_pipe(char	*input, t_token_lst *tokens_lst)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '|')
			break ;
		if (input[i] == '|')
			return (1);
		i++;
	}
	while (input[i])
	{
		i = ft_check_init3(input, i);
		if (input[i] == '\0')
			return (1);
		if (ft_check_init2(input, i))
			return (1);
		i++;
	}
	if (ft_check_init(tokens_lst))
		return (1);
	return (0);
}
