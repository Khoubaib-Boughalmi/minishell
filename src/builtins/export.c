#include "../../minishell.h"

int	ft_export(char *key, char *value)
{
	t_envp_node *node;
	t_envp_node	*prev_node;
	

	if(!check_str(key) || !check_str(value))
		return (1);
	prev_node = envp_find_node(key);
	if(prev_node && !ft_strlcmp(prev_node->value, value))
		return (1);
	else if(prev_node)
	{
		free(prev_node->value);
		prev_node->value = value;
		return (1);
	}
	node = envp_new_node(key, value);
	if(!node)
		return (0);
	envp_lst_add_back(node);
	return (1);
}

