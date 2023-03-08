#include "../../minishell.h"

int	ft_export(char *key, char *value)
{
	t_envp_node *node;

	node = envp_new_node(key, value);
	if(!node)
		return (0);
	envp_lst_add_back(node);
	return (1);
}

