#include "../../minishell.h"

void	ft_unest(char	**list_keys)
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
			gstruct->exit_status = 1;
			return ;
		}
		ptr = gstruct->export_head;
		while (ptr)
		{
			if(!ft_strlcmp(ptr->key, list_keys[j]))
			{
				envp_delete_node(i, &gstruct->export_head);
				break;
			}
			i++;
			ptr = ptr->next;
		}
		i = 0;	
		ptr = gstruct->envp_head;
		while (ptr)
		{
			if(!ft_strlcmp(ptr->key, list_keys[j]))
			{
				envp_delete_node(i, &gstruct->envp_head);
				break;
			}
			i++;
			ptr = ptr->next;
		}
	}
	gstruct->exit_status = 0;
}