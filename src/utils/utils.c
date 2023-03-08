#include "../../minishell.h"

void	free_split(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}

int	is_part_of_list(char c, char *list)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(list))
	{
		if(list[i] == c)
			return (1);
		i++;
	}
	return (0);
}