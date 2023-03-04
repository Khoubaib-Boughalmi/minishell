#include "../minishell.h"

void	free_split(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}