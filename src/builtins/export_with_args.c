/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:26:55 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/12 18:36:19 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_export_key_val(char *key)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(key[0]) && key[0] != '_') || !check_str(key))
	{
		ft_printf("minishell: not a valid identifier\n");
		return (0);
	}
	while (key[i])
	{
		if (key[i] != '_' && !(ft_isalnum(key[i])))
		{
			ft_printf("minishell: not a valid identifier\n");
			g_struct->exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_export_no_val(char **list_vars, t_export export, int i)
{
	if (!check_export_key_val(list_vars[i]))
			g_struct->exit_status = 1;
	else
	{
		export.prev_node_export = envp_find_node(list_vars[i], \
		ft_strlen(list_vars[i]), g_struct->export_head);
		if (!export.prev_node_export)
		{
			export.export_node = envp_new_node(list_vars[i], NULL, EXPORT);
			envp_lst_add_back(export.export_node, &(g_struct->export_head));
		}
	}
}

//export key and value
void	ft_export_k_v(t_export export, char *key, char *value)
{
	if (value)
	{
		if (check_export_key_val(key))
			ft_norm_1(export, key, value);
		else
			g_struct->exit_status = 1;
	}
	else
	{
		if (check_export_key_val(key))
			ft_norm_2(export, key);
	}
}

void	ft_export_with_args_core(char **list_vars, t_export export, int i)
{
	char	*key;
	char	*value;

	value = NULL;
	key = NULL;
	if (char_in_str(list_vars[i], '='))
	{
		key = get_key(list_vars[i]);
		value = get_value(list_vars[i]);
		if (!check_str(key))
		{
			printf("asdasdasddsasdasdasd\n");
			g_struct->exit_status = 1;
			free(key);
			free(value);
			return ;
		}
		ft_export_k_v(export, key, value);
		if(key)
			free(key);
		if(value)
			free(value);
	}
	else
		ft_export_no_val(list_vars, export, i);
}

void	ft_export_with_args(char **list_vars)
{
	int			i;
	char		*key;
	char		*value;
	t_export	export;

	value = NULL;
	key = NULL;
	export.prev_node_export = NULL;
	if (list_vars_len(list_vars) == 1)
	{
		ft_export_no_args();
		return ;
	}
	i = 0;
	while (list_vars[++i])
		ft_export_with_args_core(list_vars, export, i);
}
