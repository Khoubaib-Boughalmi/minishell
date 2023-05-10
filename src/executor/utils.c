/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:37:21 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 10:43:38 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_commands(t_token_lst *token_lst)
{
	int	i;
	int	count;

	count = 0;
	while (token_lst && token_lst->token->type != AST_PIPE)
	{
		i = 0;
		if (token_lst->token->type == AST_COMMAND)
		{
			while (token_lst->token->args[i])
				i++;
		}
		count += i;
		token_lst = token_lst->next;
	}
	return (count);
}

int	count_redirections(t_token_lst *token_lst)
{
	int	count;

	count = 0;
	while (token_lst && token_lst->token->type != AST_PIPE)
	{
		if (token_lst->token->type == AST_REDIRECTION)
			count ++;
		token_lst = token_lst->next;
	}
	return (count);
}

char	**get_envp_arr(void)
{
	int			i;
	int			j;
	int			len;
	t_envp_node	*ptr;
	char		**envp_str;

	i = 0;
	ptr = g_struct->envp_head;
	len = envp_list_vars_len(ptr);
	if (!len)
		return (NULL);
	envp_str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp_str)
		return (NULL);
	envp_str[len] = 0;
	while (ptr)
	{
		j = 0;
		envp_str[i] = ft_strdup(ptr->key);
		envp_str[i] = ft_strjoin(envp_str[i], "=");
		envp_str[i] = ft_strjoin(envp_str[i], ptr->value);
		ptr = ptr->next;
		i++;
	}
	return (envp_str);
}

char	*join_multiple_args(char **args)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = (char *)malloc(sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	while (args[i])
	{
		new_str = ft_strjoin(args[i], new_str);
		i++;
	}
	return (new_str);
}

int	check_ambiguous(int vars, char **original)
{
	char	*original_cpy;
	int		i;

	if (vars && !(*original))
		return (1);
	original_cpy = ft_strdup(*original);
	if (original_cpy)
	{
		expand_quotes_red(&original_cpy);
		i = 0;
		if (original_cpy)
		{
			while (original_cpy[i] && original_cpy[i] == ' ')
				i++;
			if (!original_cpy[i])
			{
				free(original_cpy);
				return (1);
			}
		}
		free(original_cpy);
	}
	return (0);
}
