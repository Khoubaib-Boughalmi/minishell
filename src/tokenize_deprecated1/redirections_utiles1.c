#include "../../minishell.h"

int	ft_check_der_left(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '<')
			return (1);
		j++;
	}
	return (0);
}

int	ft_check_der_right(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '>')
			return (1);
		j++;
	}
	return (0);
}

int	ft_check_last_der2(char	*input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '\0')
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

char	**ft_der_insert_2(char	*input, char	**str, char *c)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		m;

	i = 0;
	j = 0;
	k = ft_check_dub_der2(input);
	m = ft_check_last_der2(input);
	res = malloc((2 * ft_count_str(str) + k + m + 1) * sizeof(char *));
	while (str[i + 1])
	{
		res[j] = ft_strdup(str[i]);
		j++;
		res[j] = ft_strdup(c);
		j++;
		i++;
	}
	res[j] = ft_strdup(str[i]);
	if (m != 0)
	{
		j++;
		res[j] = ft_strdup(c);
	}
	j++;
	res[j] = 0;
	//ft_free(str);
	return (res);
}
