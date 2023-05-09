/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:36:01 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/09 12:10:20 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_norm_2_2(t_export export, char *key, char *value)
{
	if (export.prev_node_export->value)
		free(export.prev_node_export->value);
	export.prev_node_export->value = (char *)malloc(sizeof(char));
	export.prev_node_export->value[0] = '\0';
	if (export.prev_node_envp)
	{
		if (export.prev_node_envp->value)
			free(export.prev_node_envp->value);
		export.prev_node_envp->value = (char *)malloc(sizeof(char));
		export.prev_node_envp->value[0] = '\0';
	}
	else
	{
		export.env_node = envp_new_node(key, "", EXPORT);
		envp_lst_add_back(export.env_node, &(g_struct->envp_head));
	}
}

void	ft_norm_2(char **list_vars, t_export export, char *key, char *value)
{
	export.prev_node_export = envp_find_node(key, \
	ft_strlen(key), g_struct->export_head);
	export.prev_node_envp = envp_find_node(key, \
	ft_strlen(key), g_struct->envp_head);
	if (!export.prev_node_export)
	{
		export.export_node = envp_new_node(key, "", EXPORT);
		export.env_node = envp_new_node(key, "", EXPORT);
		if (!export.export_node || !export.env_node)
			return ;
		envp_lst_add_back(export.export_node, &(g_struct->export_head));
		envp_lst_add_back(export.env_node, &(g_struct->envp_head));
	}
	else
		ft_norm_2_2(export, key, value);
}

void	ft_norm_1_1(t_export export, char *value)
{
	free(export.prev_node_export->value);
	export.prev_node_export->value = value;
	if (export.prev_node_envp && export.prev_node_envp->value)
	{
		free(export.prev_node_envp->value);
		export.prev_node_envp->value = ft_strdup(value);
	}
}

void	ft_norm_1(char **list_vars, t_export export, char *key, char *value)
{
	export.prev_node_export = envp_find_node(key, ft_strlen(key), \
	g_struct->export_head);
	export.prev_node_envp = envp_find_node(key, ft_strlen(key), \
	g_struct->envp_head);
	if (export.prev_node_export && export.prev_node_export->value && \
	ft_strlcmp(export.prev_node_export->value, value))
		ft_norm_1_1(export, value);
	else if (export.prev_node_export && !export.prev_node_export->value)
	{
		export.prev_node_export->value = ft_strdup(value);
		export.env_node = envp_new_node(key, value, EXPORT);
		envp_lst_add_back(export.env_node, &(g_struct->envp_head));
	}
	else if (!export.prev_node_export)
	{
		export.export_node = envp_new_node(key, value, EXPORT);
		export.env_node = envp_new_node(key, value, EXPORT);
		if (!export.export_node || !export.env_node)
			return ;
		envp_lst_add_back(export.export_node, &(g_struct->export_head));
		envp_lst_add_back(export.env_node, &(g_struct->envp_head));
	}
}
