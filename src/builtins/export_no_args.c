/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:27:03 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/30 16:31:29 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export_no_args_core(t_envp_node *ptr)
{
	int	i;

	i = 0;
	ft_printf("declare -x %s=\"", ptr->key);
	while (ptr->value[i])
	{
		if (ptr->value[i] == '\"' || ptr->value[i] == '$')
			ft_printf("\\%c", ptr->value[i]);
		else
			ft_printf("%c", ptr->value[i]);
		i++;
	}
	ft_printf("\"\n");
}

void	ft_export_no_args(void)
{
	t_envp_node	*ptr;

	ptr = g_struct->export_head;
	while (ptr)
	{
		if (ptr->value && ptr->value[0])
			ft_export_no_args_core(ptr);
		else if (ptr->value && !ptr->value[0])
			ft_printf("declare -x %s=\"\"\n", ptr->key);
		else if (!ptr->value)
			ft_printf("declare -x %s\n", ptr->key);
		ptr = ptr->next;
	}
	g_struct->exit_status = 0;
}
