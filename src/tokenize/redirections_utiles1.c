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

int ft_cout_red(char	*input, char c)
{
	int count = 0;
	int i = 0;
	char n;

	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			n = input[i];
			i++;
			while (!input[i] || (input[i] != n && input[i] != n))
				i++;
		}
		if (input[i] == c && (input[i + 1] != c || input[i + 1] != '\0'))
			count++;
		i++;
	}
	return count;
}

char	**ft_der_insert_2(char	*input, char	**str, char *c, char *a)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		m;
	char n;

	i = 0;
	j = 0;
	k = 0;
	res = malloc((ft_count_str(str) + ft_cout_red(input, c[0]) + 3) * sizeof(char *));
	while (input[k] == ' ')
			k++;
	if (input[k] == c[0])
	{
		k++;
		if (input[k] == c[0])
		{
			k++;
			res[j] = ft_strdup(c);
		}
		else
			res[j] = ft_strdup(a);
		j++;
	}
	while (str[i])
	{
		res[j++] = ft_strdup(str[i]);
		while (input[k])
		{
			if (input[k] == '\'' || input[k] == '\"')
			{
				n = input[k];
				k++;
				while (!input[k] || input[k] != n)
					k++;
			}
			if (input[k] == c[0])
			{
				k++;
				if (input[k] == c[0])
				{
					k++;
					res[j++] = ft_strdup(c);
					break;
				}
				res[j++] = ft_strdup(a);
				break;
			}
			k++;
		}
		i++;
	}
	res[j] = 0;
	//ft_free(str);
	return (res);
}
