#include "../../minishell.h"

int	get_variable_len(char *start)
{
	size_t	i;

	i = 0;
	while (start[i] && start[i] != ' ' && start[i] != '\"' && start[i] != '\'' && start[i] != '$' && start[i] != '|' )
		i++;
	// if(start[i] == '|')
	// 	i--;
	return (i);
}