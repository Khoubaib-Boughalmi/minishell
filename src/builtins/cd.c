#include "../../minishell.h"

void	ft_cd(char *dir)
{
	if(chdir(dir))
	{
		perror("cd failed");
		gstruct->exit_status = 1;
		return ;
	}
}