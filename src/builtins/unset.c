#include "../../minishell.h"

int	ft_unest(char *key)
{
	t_envp_node	*ptr;
	int			i;

	i = 0;
	ptr = gstruct->envp_head;
	while (ptr)
	{
		if(!ft_strncmp(ptr->key, key, ft_strlen((char *)key)))
		{
			envp_delete_node(i);
			return (0);
		}
		ptr = ptr->next;
		i++;
	}
	return (127);
}