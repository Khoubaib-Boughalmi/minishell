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


int	ft_strlcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (0);
	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if(l1 != l2)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_str(char *str)
{
	if(!str || !str[0] || str[0] == '\n')
		return (0);
	return (1);
}