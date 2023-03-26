#include "../../minishell.h"

//	after detecting export function being called ft_export expects to get a 2D array of key,value pairs to be export
//	exo: 	// ft_export((char *[]){"a1=1" , "a2=2" , "a3=0", "a3=0", "a3=55", NULL});
int	check_export_key_val(char *key, char *value)
{
	int	i;

	i = 1;
	if(!check_str(key))
		return (0);
	if(!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[i])
	{
		if(key[i] != '_' && !(ft_isalnum(key[i])))
		{
			printf("ERROR : %c\n", key[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_export_with_args(char **list_vars)
{
	int			i;
	char		*key;
	t_envp_node *node;
	char		*value;
	char		**splited;
	t_envp_node	*prev_node;

	i = 0;
	while(list_vars[i])
	{
		splited = ft_split(list_vars[i], '=');
		key = splited[0];
		value = splited[1];
		if(!check_str(key) || !check_str(value))
		{
			gstruct->exit_status = 1;
			return ;
		}
		if(check_export_key_val(key, value))
		{
			prev_node = envp_find_node(key, ft_strlen(key), gstruct->export_head);
			if(prev_node && ft_strlcmp(prev_node->value, value))
			{
				free(prev_node->value);
				prev_node->value = value;
			}
			else if(!prev_node)
			{
				node = envp_new_node(key, value);
				if(!node)
					return ;
				envp_lst_add_back(node, &(gstruct->export_head));
			}
		}
		i++;
	}
}

void	ft_export_no_args()
{
	t_envp_node	*ptr;
	
	ptr = gstruct->export_head;
	while (ptr)
	{
		printf("declare -x %s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}
