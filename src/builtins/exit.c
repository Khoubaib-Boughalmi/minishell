#include "../../minishell.h"

//handle the -n flag
void	ft_exit(char	**list_vars)
{
	long long	ex_status;

	if (list_vars_len(list_vars) > 2)
	{
		printf("exit: too many arguments\n");
		gstruct->exit_status = 1;
	}
	else if(list_vars_len(list_vars) == 2)
	{
		ex_status = ft_atoi(list_vars[1]);
		// if(ex_status < 0)
		// {
		// 	ex_status = -ex_status + 1;
		// }
			// printf("negaaa");
		gstruct->exit_status = ex_status & 255;
	}
	else
		gstruct->exit_status = 0;
}