/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_execute2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:08:26 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 18:17:37 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_paths(t_envp_node *envp)
{
	char	*def;

	if (!envp)
	{
		def = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
		def = ft_strdup(def);
		return (ft_split(def, ':'));
		free(def);
	}
	while (envp)
	{
		if (ft_strnstr(envp->key, "PATH", 4))
			return (ft_split(envp->value, ':'));
		envp = envp->next;
	}
	ft_putstr_fd("minishell: No such file or directory\n", 2);
	exit(127);
}

char	*path_finder(char *cmd, t_envp_node *envp)
{
	char	*tmp;
	char	**path;
	char	*tmp2;
	int		i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	path = get_paths(envp);
	i = -1;
	while (path[++i])
	{
		tmp2 = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp2, cmd);
		free(tmp2);
		if (!access(tmp, F_OK))
		{
			free_split(path);
			return (tmp);
		}
		free(tmp);
	}
	free_split(path);
	return (0);
}
