#include "../../minishell.h"

//	after detecting export function being called ft_export expects to get a 2D array of key,value pairs to be export
//	exo: 	// ft_export((char *[]){"a1=1" , "a2=2" , "a3=0", "a3=0", "a3=55", NULL});
int	check_export_key_val(char *key, char *value)
{
	int	i;

	i = 1;
	// printf("1 %s\n", key);
	if((!ft_isalpha(key[0]) && key[0] != '_') || !check_str(key))
	{
		printf("minishell: not a valid identifier\n");
		return (0);
	}
	while (key[i])
	{
		if(key[i] != '_' && !(ft_isalnum(key[i])))
		{
			printf("minishell: not a valid identifier\n");
			gstruct->exit_status = 1;
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
	prev_node_export = NULL;
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
			if(!check_str(key))
			{
				gstruct->exit_status = 1;
				return ;
			}
			if(value)
			{
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
					else if(prev_node_export && !prev_node_export->value)
					{
						prev_node_export->value = ft_strdup(value);
						env_node = envp_new_node(key, value, EXPORT);
						envp_lst_add_back(env_node, &(gstruct->envp_head));
					}
					else if(!prev_node_export)
					{
						export_node = envp_new_node(key, value, EXPORT);
						env_node = envp_new_node(key, value, EXPORT);
						if(!export_node || !env_node)
							return ;
						envp_lst_add_back(export_node, &(gstruct->export_head));
						envp_lst_add_back(env_node, &(gstruct->envp_head));
					}
				}
				else
					gstruct->exit_status = 1;
			}
			else
			{
				if(check_export_key_val(key, value))
				{
					prev_node_export = envp_find_node(key, ft_strlen(key), gstruct->export_head);
					prev_node_envp = envp_find_node(key, ft_strlen(key), gstruct->envp_head);
					if(!prev_node_export)
					{
						export_node = envp_new_node(key, "", EXPORT);
						env_node = envp_new_node(key, "", EXPORT);
						if(!export_node || !env_node)
							return ;
						envp_lst_add_back(export_node, &(gstruct->export_head));
						envp_lst_add_back(env_node, &(gstruct->envp_head));
					}
					else
					{
						if(prev_node_export->value)
							free(prev_node_export->value);
						prev_node_export->value = (char *)malloc(sizeof(char));
						prev_node_export->value[0] = '\0';
						if(prev_node_envp)
						{
							if(prev_node_envp->value)
								free(prev_node_envp->value);
							prev_node_envp->value = (char *)malloc(sizeof(char));
							prev_node_envp->value[0] = '\0';
						}
						else
						{
							env_node = envp_new_node(key, "", EXPORT);
							envp_lst_add_back(env_node, &(gstruct->envp_head));
						}
					}
				}
			}
		}
		else
		{
			if(!check_export_key_val(list_vars[i], value))
				gstruct->exit_status = 1;
			else
			{
				prev_node_export = envp_find_node(list_vars[i], ft_strlen(list_vars[i]), gstruct->export_head);
				if(!prev_node_export)
				{
					export_node = envp_new_node(list_vars[i], NULL, EXPORT);
					envp_lst_add_back(export_node, &(gstruct->export_head));
				}
			}
		}
		i++;
	}
	// gstruct->exit_status = 0;
}

void	ft_export_no_args()
{
	int			i;
	t_envp_node	*ptr;
	
	i = 0;
	ptr = gstruct->export_head;
	while (ptr)
	{
		i = 0;
		if(ptr->value && ptr->value[0])
		{
			ft_printf("declare -x %s=\"", ptr->key);
			while (ptr->value[i])
			{
				if(ptr->value[i] == '\"' || ptr->value[i] == '$')
					ft_printf("\\%c", ptr->value[i]);
				else
					ft_printf("%c", ptr->value[i]);
				i++;
			}
			ft_printf("\"\n");
		}
		else if(ptr->value && !ptr->value[0])
			ft_printf("declare -x %s=\"\"\n", ptr->key);
		else if(!ptr->value)
			ft_printf("declare -x %s\n", ptr->key);
		ptr = ptr->next;
	}
	gstruct->exit_status = 0;
}
