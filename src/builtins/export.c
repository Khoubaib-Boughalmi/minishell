#include "../../minishell.h"

// void	ft_export(char *key, char *value)
// {
// 	t_envp_node *node;
// 	t_envp_node	*prev_node;
	
// 	if(!check_str(key) || !check_str(value))
// 	{
// 		gstruct->exit_status = 1;
// 		return ;
// 	}
// 	prev_node = envp_find_node(key, ft_strlen(key));
// 	if(prev_node && !ft_strlcmp(prev_node->value, value))
// 		return ;
// 	else if(prev_node)
// 	{
// 		free(prev_node->value);
// 		prev_node->value = value;
// 	}
// 	node = envp_new_node(key, value);
// 	if(!node)
// 		return ;
// 	envp_lst_add_back(node);
// }


//	after detecting export function being called ft_export expects to get a 2D array of key,value pairs to be export
//	exo: 	// ft_export((char *[]){"a1=1" , "a2=2" , "a3=0", "a3=0", "a3=55", NULL});
void	ft_export(char **list_vars)
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
		prev_node = envp_find_node(key, ft_strlen(key));
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
			envp_lst_add_back(node);
		}
		i++;
	}
}

