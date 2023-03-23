#include "../../minishell.h"

int	ft_check_mul_der(char	*input, char c)
{
	int		i;
	int		j;
	char	n;
	int		k;

	i = 0;
	while (input[i])
	{
		k = 0;
		if (input[i] == '\'' || input[i] == '\"')
		{
			n = input[i];
			i++;
			while (!input[i] || (input[i] != n && input[i] != n))
				i++;
			if (!input[i])
				return (1);
		}
		if (input[i] == c)
		{
			j = i + 1;
			while (input[j])
			{
				if (input[j] == c)
					k++;
				else
					break ;
				j++;
			}
		}
		if (k > 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_str_der(char	**str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	ft_check_dub_der(char	*input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c && input[i + 1] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_last_der(char	*input, char c)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == c && input[i + 1] == '\0')
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

char	**ft_der_insert(char	*input, char	**str, char *c)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		m;

	j = 0;
	i = 0;
	k = ft_check_dub_der(input , c[0]);
	m = ft_check_last_der(input, c[0]);
	res = malloc((2 * ft_count_str_der(str) + k + m + 1) * sizeof(char *));
	while (str[i + 1])
	{
		res[j] = ft_strdup(str[i]);
		j++;
		if (k == 1)
		{
			if (c[0] == '>')
				res[j] = ft_strdup(">>");
			else
				res[j] = ft_strdup("<<");
		}
		else
			res[j] = ft_strdup(c);
		j++;
		i++;
	}
	res[j] = ft_strdup(str[i]);
	if (m != 0)
	{
		j++;
		if (m == 2)
		{
			if (c[0] == '>')
				res[j] = ft_strdup(">>");
			else
				res[j] = ft_strdup("<<");
		}
        res[j] = ft_strdup(c);
	}
	j++;
	res[j] = 0;
	//ft_free(str);
	return (res);
}
