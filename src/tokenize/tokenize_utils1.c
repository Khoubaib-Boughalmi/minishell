#include "../../minishell.h"

int	ft_count_str(char	**str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	ft_free_token(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_check_last_pipe(char	*input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '\0')
		{
			j = i + 1;
			while (input[j] != '\0')
			{
				if (input[i] != ' ' && input[i] != '\t')
					break ;
				j++;
			}
			if (input[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_pipe_insert(char	*input, char	**str)
{
	char	**res;
	int		i;
	int		j;
	int		m;

	i = 0;
	j = 0;
	m = ft_check_last_pipe(input);
	res = malloc((2 * ft_count_str(str) + m + 1) * sizeof(char *));
	while (str[i + 1])
	{
		res[j] = ft_strdup(str[i]);
		j++;
		res[j] = ft_strdup("|");
		j++;
		i++;
	}
	res[j] = ft_strdup(str[i]);
	if (m != 0)
	{
		j++;
		res[j] = ft_strdup("|");
	}
	j++;
	res[j] = 0;
	ft_free_token(str);
	return (res);
}
