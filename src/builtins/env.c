#include "../../minishell.h"

int	ft_env(void)
{
	t_envp_node	*ptr;

	ptr = gstruct->envp_head;
	if(!ptr)
		return (1);
	while (ptr)
	{
		printf("%s=%s\n", ptr->key,  ptr->value);
		ptr = ptr->next;
	}
	return (0);
}