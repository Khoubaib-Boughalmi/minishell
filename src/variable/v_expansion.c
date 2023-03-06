#include "../../minishell.h"

char	*variable_expansion(char *key)
{
	t_envp_node *ptr;

	ptr = gstruct->envp_head;
	while (ptr)
	{
		if(!ft_strncmp(ptr->key, key, ft_strlen(key)))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}