#include "../../minishell.h"

int	ft_unest(char *key)
{
	t_envp_node	*ptr;
	int			i;

	i = 0;
	if(!check_str(key))
		return (1);
	ptr = gstruct->envp_head;
	while (ptr)
	{
		if(!ft_strlcmp(ptr->key, key))
		{
			envp_delete_node(i);
			return (0);
		}
		ptr = ptr->next;
		i++;
	}
	return (127);
}