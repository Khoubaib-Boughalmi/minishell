/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:24:14 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/29 15:25:20 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char	*cmd)
{
	int		i;
	char	**builtins;

	i = 0;
	builtins = ft_split("cd echo exit export unset env pwd", ' ');
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

int	list_vars_len(char **list_cmds)
{
	int	i;

	i = 0;
	while (list_cmds[i])
		i++;
	return (i);
}

int	envp_list_vars_len(t_envp_node *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

int	char_in_str(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

void	handle_builtin(char **list_cmds)
{
	if (!ft_strlcmp(list_cmds[0], "cd"))
		ft_cd(list_cmds);
	if (!ft_strlcmp(list_cmds[0], "pwd"))
		ft_pwd();
	if (!ft_strlcmp(list_cmds[0], "echo"))
		ft_echo(list_cmds);
	if (!ft_strlcmp(list_cmds[0], "export"))
		ft_export_with_args(list_cmds);
	if (!ft_strlcmp(list_cmds[0], "unset"))
		ft_unset(list_cmds);
	if (!ft_strlcmp(list_cmds[0], "env"))
		ft_env();
	if (!ft_strlcmp(list_cmds[0], "exit"))
		ft_exit(list_cmds);
}
