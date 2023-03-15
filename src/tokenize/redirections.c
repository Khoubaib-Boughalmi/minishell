#include "../../minishell.h"

char	**ft_split_der(char	**str, char *input)
{
	int		i;
	int		j;
	int		k;
	int		m;
	char	**temp;
	char	**res;

	i = 0;
	k = 0;
	j = 0;
	res = malloc((ft_count_str(str) + ft_count_der(str) + 1) * sizeof(char *));
	while (str[i])
	{
		k = 0;
		if (ft_check_der_right(str[i]))
		{
			m = ft_check_dub_der2(str[i]);
			temp = ft_split_qotes(str[i], '>');
			if (m == 1)
				temp = ft_der_insert_2(str[i], temp, ">>");
			else
				temp = ft_der_insert_2(str[i], temp, ">");
			while (temp[k])
				res[j++] = ft_strdup(temp[k++]);
		}
		else if (ft_check_der_left(str[i]))
		{
			m = ft_check_dub_der2(str[i]);
			temp = ft_split_qotes(str[i], '<');
			if (m == 1)
				temp = ft_der_insert_2(str[i], temp, "<<");
			else
				temp = ft_der_insert_2(str[i], temp, "<");
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
