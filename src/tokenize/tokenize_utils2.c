#include "../../minishell.h"

int ft_check_der(char *str)
{
	int j = 0;
	char c;
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
			return 1;
		j++;
	}
	return 0;
}

int ft_check_pipe(char *str)
{
	int j = 0;

	if (str[0] == '|')
		return 1;
	return 0;
}

char *ft_strdup_file(char	*s)
{
	char	*str;
	int		i;
	int		len;

	len = ft_strlen(s);
	while (s[len] != '<' && s[len] != '>')
	{
		len--;
	}
	len++;
	i = ft_strlen(s) - len;
	str = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while(s[len])
	{
		str[i] = s[len];
		len++;
		i++;
	}

	str[i] = '\0';
	return (str);
}

int	ft_check_dub_der2(char	*input)
{
	int i = 0;

	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (1);
		i++;
	}
	return (0);
}
int ft_check_last_der2(char	*input)
{
	int i = 0;
	int j;

	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '\0')
		{
			j = i + 1;
			while (input[j] != '\0')
			{
				if (input[i] != ' ' && input[i] != '\t')
					break;
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
	char **res;
	int i = 0;
	int j = 0;
	int k;
	int m;

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

int ft_check_der_left(char *str)
{
	int j = 0;
	while (str[j])
	{
		if (str[j] == '<')
			return 1;
		j++;
	}
	return 0;
}

int ft_check_der_right(char *str)
{
	int j = 0;
	while (str[j])
	{
		if (str[j] == '>')
			return 1;
		j++;
	}
	return 0;
}

char	**ft_split_der(char	**str, char *input)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int m;
	char			**temp;
	char **res;

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

	return res;
}

void	ft_lst_token_add_back(t_token_lst **lst, t_token_lst *new)
{
	t_token_lst	*ptr;

	ptr = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}
