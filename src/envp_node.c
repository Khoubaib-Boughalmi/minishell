#include "../minishell.h"


t_envp_node	*new_envp_node(char *key, char *value)
{
	t_envp_node	*node;

	node = (t_envp_node *)malloc(sizeof(t_envp_node));
	if(!node)
		return (0);
	node->key = (char *)malloc(ft_strlen((char *)key) + 1);
	node->value = (char *)malloc(ft_strlen((char *)value) + 1);
	if(!node->key || !node->value)
		return (0);
	ft_strlcpy(node->key, key, ft_strlen((char *)key) + 1);
	ft_strlcpy(node->value, value, ft_strlen((char *)value) + 1);
	node->next = NULL;
	return (node);
}

void envp_lst_add_back(t_envp_node *node)
{
	t_envp_node	*head_copy;

	head_copy = gstruct->envp_head;
	if(gstruct->envp_head == NULL)
		gstruct->envp_head = node;
	else
	{
		while (head_copy->next)
			head_copy = head_copy->next;
		head_copy->next = node;
	}
}