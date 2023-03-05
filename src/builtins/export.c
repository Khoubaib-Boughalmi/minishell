#include "../../minishell.h"

int	ft_export(char *key, char *value)
{
	t_envp_node	*ptr;
	t_envp_node *node;

	ptr = gstruct->envp_head;
	while (ptr->next)
		ptr = ptr->next;
	node = envp_new_node(key, value);
	if(!node)
		return (0);
	envp_lst_add_back(node);
	return (1);
}