#include "../../minishell.h"

void	ft_env(void)
{
	t_envp_node	*ptr;

	ptr = g_struct->envp_head;
	if(!ptr)
	{
		g_struct->exit_status = 1;
		return ;
	}
	if(!envp_find_node("PATH", 4, g_struct->envp_head))
	{
		ft_printf("minishell: env: No such file or directory\n");
		g_struct->exit_status = 1;
		return ;
	}
	while (ptr)
	{
		printf("%s=%s\n", ptr->key,  ptr->value);
		ptr = ptr->next;
	}
	g_struct->exit_status = 0;
}