#include "../../minishell.h"

int	ft_check_mul_pipe(char	*input)
{
	int i = 0;
	int j;
	int k;

	while (input[i])
	{
		if (input[i] != ' '&& input[i] != '\t' && input[i] != '|')
			break ;
		if (input[i] == '|')
			return (1);
		i++;
	}
	while (input[i])
	{
		k = 0;
		if (input[i] == '|')
		{
			j = i + 1;
			while(input[j])
			{
				if (input[j] == '|')
					k++;
				else
					break;
				j++;
			}
		}
		if (k > 1)
			return (1);
		i++;
	}
	return (0);
}

int ft_check_space_pipe(char **temp)
{
	int i = 0;
	char **tmp;

	while (temp[i])
	{
		tmp = ft_split(temp[i], ' ');
		if (!*tmp)
			return (1);
		i++;
	}
	return (0);
}
