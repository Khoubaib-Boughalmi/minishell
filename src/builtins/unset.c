#include "../../minishell.h"

void	ft_unset(char	**list_keys)
{
	int			i;
	int			j;
	char		*key;
	t_envp_node	*ptr;
	char		**splited;

	j = 0;
	while (list_keys[++j])
	{
		i = 0;
		if(!check_str(list_keys[j]))
		{
			g_struct->exit_status = 1;
			return ;
		}
		ptr = g_struct->export_head;
		while (ptr)
		{
			if(!ft_strlcmp(ptr->key, list_keys[j]))
			{
				envp_delete_node(i, &g_struct->export_head);
				break;
			}
			i++;
			ptr = ptr->next;
		}
		i = 0;	
		ptr = g_struct->envp_head;
		while (ptr)
		{
			if(!ft_strlcmp(ptr->key, list_keys[j]))
			{
				envp_delete_node(i, &g_struct->envp_head);
				break;
			}
			i++;
			ptr = ptr->next;
		}
	}
	g_struct->exit_status = 0;
}