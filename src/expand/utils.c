#include "../../minishell.h"

int	get_key_len(char *start)
{
	size_t	i;

	i = 0;
	while (start[i] && start[i] != ' ' && start[i] != '\"')
		i++;
	i--;
	return (i);
}