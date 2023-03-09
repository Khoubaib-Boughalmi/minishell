#include "../../minishell.h"

void	ft_unest(char *key)
{
	t_envp_node	*ptr;
	int			i;

	i = 0;
	if(!check_str(key))
	{
		gstruct->exit_status = 1;
		return ;
	}
	ptr = gstruct->envp_head;
	while (ptr)
	{
		if(!ft_strlcmp(ptr->key, key))
		{
			envp_delete_node(i);
			return ;
		}
		ptr = ptr->next;
		i++;
	}
	gstruct->exit_status = 127;
}