/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:36:28 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/08 22:16:44 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envp_node	*envp_new_node(char *key, char *value, t_envp envp_val)
{
	t_envp_node	*node;

	node = (t_envp_node *)malloc(sizeof(t_envp_node));
	node->key = (char *)malloc(ft_strlen((char *)key) + 1);
	if (value && ft_strlen(value) > 0)
		node->value = (char *)malloc(ft_strlen((char *)value) + 1);
	else if (value && ft_strlen(value) == 0)
		node->value = (char *)malloc(sizeof(char));
	if (!value)
	{
		if (envp_val == ENVP)
			node->value = ft_strdup(0);
		else
			node->value = NULL;
	}
	if (!node->key)
		return (0);
	ft_strlcpy(node->key, key, ft_strlen((char *)key) + 1);
	if (value && ft_strlen(value) > 0)
		ft_strlcpy(node->value, value, ft_strlen((char *)value) + 1);
	else if (value && ft_strlen(value) == 0)
		node->value[0] = '\0';
	node->next = NULL;
	return (node);
}

void	envp_lst_add_back(t_envp_node *node, t_envp_node **head)
{
	t_envp_node	*head_copy;

	head_copy = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (head_copy->next)
			head_copy = head_copy->next;
		head_copy->next = node;
	}
}

void	envp_delete_node(int pos, t_envp_node **head)
{
	int			i;
	t_envp_node	*current;
	t_envp_node	*previous;

	i = -1;
	current = *head;
	if (pos == 0)
	{
		*head = (*head)->next;
		free(current);
	}
	else
	{
		while (current->next && ++i < pos)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}

//can be used for variable expansion
t_envp_node	*envp_find_node(char *key, size_t len, t_envp_node *head)
{
	t_envp_node	*ptr;

	ptr = head;
	if (!len)
		return ((void *)0);
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, key, get_variable_len(key)))
			return (ptr);
		ptr = ptr->next;
	}
	return ((void *)0);
}
