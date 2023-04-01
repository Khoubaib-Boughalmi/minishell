#include "../../minishell.h"

void	ft_cd(char **list_vars)
{
	t_envp_node *home_node;


	if (list_vars_len(list_vars) > 2)
		printf("cd: too many arguments\n");
	else 
	{
		if(!list_vars[1] || !ft_strlcmp(list_vars[1], "~"))
		{
			home_node = envp_find_node("HOME", ft_strlen("HOME"), gstruct->envp_head);
			if (!home_node)
			{
				printf("HOME environment variable not set\n"); //setup exit status
				return ;
			}
			if(chdir(home_node->value))
			{
				perror("cd failed");
				gstruct->exit_status = 1;
				return ;
			}
			return ;
		}
		if (chdir(list_vars[1]))
		{
			perror("cd failed");
			gstruct->exit_status = 1;
			return ;
		}
	}
}
