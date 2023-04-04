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
	t_envp_node *export_node;
	t_envp_node *env_node;
	char		*value;
	char		**splited;
	t_envp_node	*prev_node_export;
	t_envp_node	*prev_node_envp;

	i = 0;
	if(list_vars_len(list_vars) == 1)
	{
		ft_export_no_args();
		return ;
	}
	i=1;
	while(list_vars[i])
	{
		if(char_in_str(list_vars[i], '='))
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
				prev_node_export = envp_find_node(key, ft_strlen(key), gstruct->export_head);
				prev_node_envp = envp_find_node(key, ft_strlen(key), gstruct->envp_head);				
				if(prev_node_export && prev_node_export->value && ft_strlcmp(prev_node_export->value, value))
				{
					free(prev_node_export->value);
					prev_node_export->value = value;
					if(prev_node_envp && prev_node_envp->value)
					{
						free(prev_node_envp->value);
						prev_node_envp->value = ft_strdup(value);
					}
				}
				else if(!prev_node_export)
				{
					export_node = envp_new_node(key, value);
					env_node = envp_new_node(key, value);
					if(!export_node || !env_node)
						return ;
					envp_lst_add_back(export_node, &(gstruct->export_head));
					envp_lst_add_back(env_node, &(gstruct->envp_head));
				}
			}
		}
		else
		{	
			prev_node_export = envp_find_node(list_vars[i], ft_strlen(list_vars[i]), gstruct->export_head);
			if(!prev_node_export)
			{
				export_node = envp_new_node(list_vars[i], NULL);
				if(!export_node)
					return ;
				envp_lst_add_back(export_node, &(gstruct->export_head));
			}
		}
		i++;
	}
	gstruct->exit_status = 0;
}

void	ft_export_no_args()
{
	t_envp_node	*ptr;
	
	ptr = gstruct->export_head;
	while (ptr)
	{
		if(ptr->value[0])
			printf("declare -x %s=\"%s\"\n", ptr->key, ptr->value);
		else
			printf("declare -x %s\n", ptr->key);
		ptr = ptr->next;
	}
	gstruct->exit_status = 0;
}
