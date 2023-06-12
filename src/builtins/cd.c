/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:48:35 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/12 18:14:17 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd_core(void)
{
	t_envp_node	*home_node;

	home_node = envp_find_node("HOME", ft_strlen("HOME"), \
	g_struct->envp_head);
	if (!home_node)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (0);
	}
	if (chdir(home_node->value))
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		g_struct->exit_status = 1;
		return (0);
	}
	return (0);
}

void	ft_update_pwd_export(char *buff)
{
	t_envp_node	*pwd_export;	
	t_envp_node	*oldpwd_export;

	pwd_export = envp_find_node("PWD", 3, g_struct->export_head);
	oldpwd_export = envp_find_node("OLDPWD", 3, g_struct->export_head);
	if (pwd_export && oldpwd_export)
	{
		free(oldpwd_export->value);
		oldpwd_export->value = ft_strdup(pwd_export->value);
		free(pwd_export->value);
		pwd_export->value = ft_strdup(buff);
	}
}

void	ft_update_pwd(void)
{
	t_envp_node	*pwd_env;	
	t_envp_node	*oldpwd_env;	
	char		buff[6144];

	if (getcwd(buff, sizeof(buff)))
	{
		pwd_env = envp_find_node("PWD", 3, g_struct->envp_head);
		oldpwd_env = envp_find_node("OLDPWD", 3, g_struct->envp_head);
		if (pwd_env && oldpwd_env)
		{
			free(oldpwd_env->value);
			oldpwd_env->value = ft_strdup(pwd_env->value);
			free(pwd_env->value);
			pwd_env->value = ft_strdup(buff);
		}
		ft_update_pwd_export(buff);
	}
}

void	ft_cd(char **list_vars)
{
	if (list_vars_len(list_vars) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_struct->exit_status = 1;
	}
	else
	{
		if (!list_vars[1] || !ft_strlcmp(list_vars[1], "~"))
		{
			if (!ft_cd_core())
				return ;
		}
		if (chdir(list_vars[1]))
		{
			perror("minishell: ");
			g_struct->exit_status = 1;
			return ;
		}
		ft_update_pwd();
	}
	g_struct->exit_status = 0;
}
