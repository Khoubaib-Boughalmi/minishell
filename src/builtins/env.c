#include "../../minishell.h"

void ft_env(void)
{
	t_envp_node	*head_copy;

	head_copy = gstruct->envp_head;
	while (head_copy)
	{
		printf("%s=%s\n", head_copy->key,  head_copy->value);
		head_copy = head_copy->next;
	}
}