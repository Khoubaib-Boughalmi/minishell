#include "../../minishell.h"

void	ft_export(char *key, char *value)
{
	t_envp_node *node;
	t_envp_node	*prev_node;
	
	if(!check_str(key) || !check_str(value))
	{
		gstruct->exit_status = 1;
		return ;
	}
	prev_node = envp_find_node(key, ft_strlen(key));
	if(prev_node && !ft_strlcmp(prev_node->value, value))
		return ;
	else if(prev_node)
	{
		free(prev_node->value);
		prev_node->value = value;
	}
	node = envp_new_node(key, value);
	if(!node)
		return ;
	envp_lst_add_back(node);
}

