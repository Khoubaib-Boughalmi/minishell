#include "../../minishell.h"

void	ft_env(void)
{
	t_envp_node	*ptr;

	ptr = gstruct->envp_head;
	if(!ptr)
	{
		gstruct->exit_status = 1;
		return ;
	}
	while (ptr)
	{
		printf("%s=%s\n", ptr->key,  ptr->value);
		ptr = ptr->next;
	}
	gstruct->exit_status = 0;
}