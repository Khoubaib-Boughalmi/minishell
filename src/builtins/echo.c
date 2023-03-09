#include "../../minishell.h"

//handle the -n flag
int	ft_echo(char *str)
{
	if(!check_str(str))
		printf("\n");
	else
		printf("%s\n", str);
	return (0);
}