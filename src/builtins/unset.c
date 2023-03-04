#include "../../minishell.h"

void ft_unest(char *key)
{
	t_envp_node	*head_copy;
	int			i;

	i = 0;
	head_copy = gstruct->envp_head;
	while (head_copy)
	{
		if(!ft_strncmp(head_copy->key, key, ft_strlen((char *)key)))
		{
			envp_delete_node(i);
			break;
		}
		head_copy = head_copy->next;
		i++;
	}
}