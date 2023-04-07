#include "../../minishell.h"

void	ft_pwd(void)
{
	char buff[6144];

	if(getcwd(buff, sizeof(buff)))
		printf("%s\n", buff);
	else
		gstruct->exit_status = 1;
	gstruct->exit_status = 0;
}