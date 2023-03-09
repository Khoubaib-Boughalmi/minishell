#include "../../minishell.h"

void	ft_pwd(void)
{
	char buff[4096];

	if(getcwd(buff, sizeof(buff)))
		printf("%s\n", buff);
	else
		gstruct->exit_status = 1;
}