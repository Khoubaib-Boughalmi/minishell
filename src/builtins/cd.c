#include "../../minishell.h"

int	ft_cd(char *dir)
{
	if(chdir(dir))
		perror("cd failed");
	return (0);
}