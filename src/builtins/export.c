#include "../../minishell.h"

int	ft_export(char *key, char *value)
{
	t_envp_node *node;
	t_envp_node	*prev_node;
	
	prev_node = envp_find_node(key);
	if(prev_node && !ft_strncmp(prev_node->value, value, ft_strlen(value)))
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

