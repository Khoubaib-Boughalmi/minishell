#include "../../minishell.h"

//handle the -n flag
void	ft_exit(char	**list_vars)
{
	long long	ex_status;

	int	i;

	i = 0;
	if(list_vars[1])
	{
		if(list_vars[1][0] == '-')
			i++;
		while (list_vars[1][i])
		{
			if(!ft_isdigit(list_vars[1][i]))
			{
				printf("minishell: exit: %s: numeric argument required\n", list_vars[1]);
				exit(2);
			}
			i++;
		}
	}
	if (list_vars_len(list_vars) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		exit(1);
	}
	else if(list_vars_len(list_vars) == 2)
	{
		ex_status = ft_atoi(list_vars[1]);
		gstruct->exit_status = ex_status & 255;
		exit(gstruct->exit_status);
	}
	else
		exit(gstruct->exit_status);
	// gstruct->exit_status = 0;
}