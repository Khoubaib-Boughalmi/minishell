/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:44:27 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/12 16:35:12 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_g_struct(void)
{
	g_struct = (t_global_struct *)malloc(sizeof(t_global_struct));
	if (!g_struct)
		return (0);
	ft_memset(g_struct, 0, sizeof(t_global_struct));
	g_struct->ppin = 0;
	g_struct->ppout = 1;
	return (1);
}

int	init_envp(char **envp)
{
	t_envp_node	*node;
	int			i;
	char		*key;
	char		*value;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		node = envp_new_node(key, value, ENVP);
		if (!node)
			return (0);
		envp_lst_add_back(node, &(g_struct->envp_head));
		free(key);
		free(value);
		i++;
	}
	if (!duplicate_list_export())
		return (0);
	return (1);
}

int	is_builtin2(char *cmd)
{
	int		i;
	char	**builtins;

	i = 0;
	builtins = ft_split("cd exit export unset pwd", ' ');
	if (!builtins)
		return (0);
	while (builtins[i])
	{
		if (cmd)
		{
			if (!ft_strlcmp(builtins[i], cmd))
			{
				free_split(builtins);
				return (1);
			}
		}
		i++;
	}
	free_split(builtins);
	return (0);
}

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
