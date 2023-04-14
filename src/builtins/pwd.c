#include "../../minishell.h"

void	ft_pwd(void)
{
	char buff[6144];

	if(getcwd(buff, sizeof(buff)))
		printf("%s\n", buff);
	else
		g_struct->exit_status = 1;
	g_struct->exit_status = 0;
}