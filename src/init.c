#include "../minishell.h"

int	init_gstruct()
{
	//initialize everything with 0
	gstruct = (t_global_struct *)malloc(sizeof(t_global_struct));
	if (!gstruct)
		return (0);
	ft_memset(gstruct, 0, sizeof(t_global_struct));
	gstruct->ppin = 0;
	gstruct->ppout = 1;
	return (1);
}

int init_envp(char **envp)
{
	t_envp_node	*node;
	char		**envp_split;
	int			i;

	i = 0;
	if(!envp)
		return (0);
	while (envp[i])
	{
		envp_split = ft_split(envp[i], '=');
		node = envp_new_node(envp_split[0], envp_split[1]);
		if(!node)
			return (0);
		envp_lst_add_back(node, &(gstruct->envp_head));
		free_split(envp_split);
		i++;
	}
	if(!duplicate_list_export())
		return (0);
	return (1);
}