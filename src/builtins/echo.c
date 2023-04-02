#include "../../minishell.h"

//handle the -n flag
void	ft_echo(char	**list_vars)
{
	int	i;

	i = 1;
	if(!check_str(list_vars[1]))
		printf("\n");
	else
	{
		if(ft_strlcmp(list_vars[1], "-n"))
		{
			while (list_vars[i])
			{
				if(list_vars[i + 1])
					printf("%s ", list_vars[i++]);
				else
					printf("%s\n", list_vars[i++]);
			}
		}
		else
		{
			i = 2;
			while (list_vars[i])
			{
				if(list_vars[i + 1])
					printf("%s ", list_vars[i++]);
				else
					printf("%s", list_vars[i++]);
			}
		}
	}
}