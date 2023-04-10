#include "../../minishell.h"

void	ft_cd(char **list_vars)
{
	t_envp_node *home_node;


	if (list_vars_len(list_vars) > 2)
	{
		ft_printf("cd: too many arguments\n");
		gstruct->exit_status = 1;
	}
	else 
	{
		if(!list_vars[1] || !ft_strlcmp(list_vars[1], "~"))
		{
			home_node = envp_find_node("HOME", ft_strlen("HOME"), gstruct->envp_head);
			if (!home_node)
			{
				ft_printf("minishell: cd: HOME not set\n");
				return ;
			}
			if(chdir(home_node->value))
			{
				ft_printf("minishell: %s: No such file or directory\n", home_node->value);
				gstruct->exit_status = 1;
				return ;
			}
			return ;
		}
		if (chdir(list_vars[1]))
		{
			perror("minishell: ");
			gstruct->exit_status = 1;
			return ;
		}
	}
	gstruct->exit_status = 0;
}
