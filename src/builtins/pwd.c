#include "../../minishell.h"

int ft_pwd(void)
{
	char buff[4096];

	if(getcwd(buff, sizeof(buff)))
		printf("%s\n", buff);
	else
		return (1);
	return (0);
}