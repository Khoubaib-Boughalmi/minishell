#include "../../minishell.h"

//handle the -n flag
void	ft_echo(char *str, int flag)
{
	if(!check_str(str))
		printf("\n");
	else
	{
		if(!flag)
			printf("%s\n", str);
		else
			printf("%s", str);
	}
}