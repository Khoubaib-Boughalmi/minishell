#include "../../minishell.h"

int	ft_check_mul_pipe(char	*input)
{
	int		i;
	int		j;
	char	n;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '|')
			break ;
		if (input[i] == '|')
			return (1);
		i++;
	}
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			n = input[i];
			i++;
			while (!input[i] || (input[i] != n && input[i] != n))
				i++;
			if (input[i] == '\0')
				return (1);
		}
		if (input[i] == '|')
		{
			j = i + 1;
			while (input[j])
			{
				if (input[j] == '|')
					return (1);
				else
					break ;
				j++;
			}
		}
		i++;
	}
	return (0);
}
