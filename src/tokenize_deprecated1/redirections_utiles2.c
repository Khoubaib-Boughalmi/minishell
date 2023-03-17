#include "../../minishell.h"

int	ft_check_dub_der2(char	*input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_der(char *str)
{
	int		j;
	char	c;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			c = str[j];
			j++;
			while (!str[j] || (str[j] != c && str[j] != c))
				j++;
		}
		if (str[j] == '>' || str[j] == '<')
			return (1);
		j++;
	}
	return (0);
}
