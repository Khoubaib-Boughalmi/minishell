#include "../../minishell.h"

int	ft_export(char *key, char *value)
{
	t_envp_node	*head_copy;
	t_envp_node *node;

	head_copy = gstruct->envp_head;
	while (head_copy->next)
		head_copy = head_copy->next;
	node = new_envp_node(key, value);
	if(!node)
		return (0);
	envp_lst_add_back(node);
	return (1);
}