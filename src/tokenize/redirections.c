#include "../../minishell.h"

int if_der_exe(char	*str,char	n)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == n)
			return 1;
		i++;
	}
	return 0;
}

char	**ft_split_der(char	**str, char *input, char n)
{
	int		i;
	int		j;
	int		k;
	int		m;
	char	**temp;
	char	**res;

	i = 0;
	j = 0;
	res = malloc((ft_count_str(str) + ft_count_der(str, n) + 1) * sizeof(char *));
	while (str[i])
	{
		k = 0;
		if (n == '>' && if_der_exe(str[i], n))
		{
			temp = ft_split_qotes(str[i], '>');
			temp = ft_der_insert_2(str[i], temp, ">>", ">");
			while (temp[k])
				res[j++] = ft_strdup(temp[k++]);
		}
		else if (n == '<' && if_der_exe(str[i], n))
		{
			temp = ft_split_qotes(str[i], '<');
			temp = ft_der_insert_2(str[i], temp, "<<", "<");
			while (temp[k])
				res[j++] = ft_strdup(temp[k++]);
		}
		else
			res[j++] = ft_strdup(str[i]);
		i++;
	}
	res[j] = 0;
	ft_free_token(str);
	return (res);
}
