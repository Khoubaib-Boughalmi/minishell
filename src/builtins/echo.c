#include "../../minishell.h"

//handle the -n flag
int	ft_echo(char *str)
{
	if(!str || !str[0]|| str[0] == '\n')
		printf("\n");
	else
		printf("%s\n", str);
	return (0);
}