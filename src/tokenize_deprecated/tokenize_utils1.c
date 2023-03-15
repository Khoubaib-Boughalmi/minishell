#include "../../minishell.h"

int ft_count_str(char	**str)
{
	int count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	ft_check_dub_pipe(char	*input)
{
	int i = 0;

	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int ft_check_last_pipe(char	*input)
{
	int i = 0;
	int j;

	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '\0')
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

char	**ft_pipe_insert(char	*input, char	**str)
{
	char **res;
	int i = 0;
	int j = 0;
	int k;
	int m;

	k = ft_check_dub_pipe(input);
	m = ft_check_last_pipe(input);
	res = malloc((2 * ft_count_str(str) + k + m + 1) * sizeof(char *));
	while (str[i + 1])
	{
		res[j] = ft_strdup(str[i]);
		j++;
		if (k == 1)
			res[j] = ft_strdup("||");
		else
			res[j] = ft_strdup("|");
		j++;
		i++;
	}
	res[j] = ft_strdup(str[i]);
	if (m != 0)
	{
		j++;
		if (m == 2)
			res[j] = ft_strdup("||");
		res[j] = ft_strdup("|");
	}
	j++;
	res[j] = 0;
	//ft_free(str);
	return (res);
}

int ft_count_der(char	**str)
{
	int i;
	int j;
	int count = 0;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '<' || str[i][j] == '>')
			{
				count++;
				while (str[i][j] == '<' || str[i][j] == '>')
					j++;
			}
			j++;
		}
		i++;
	}
	return (2 * count);
}

char *ft_strdup_arg(char	*s)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (s[len] != '\0')
	{
		if (s[len] == '<' || s[len] == '>')
			break;
		len++;
	}
	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strdup_der(char	*s)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	len = 0;
	while (s[len] != '<' && s[len] != '>')
		len++;
	j = ft_strlen(s);
	while (s[j] != '<' && s[j] != '>')
		j--;
	j++;
	len = j - len;
	i = 0;
	j = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s[i] != '<' && s[i] != '>')
		i++;
	if (s[i] != '\0' && s[i] == '>' && s[i + 1] == '>')
		str = ft_strdup(">>");
	else if (s[i] != '\0' && s[i] == '<' && s[i + 1] == '<')
		str = ft_strdup("<<");
	else if (s[i] != '\0' && s[i] == '<')
		str = ft_strdup("<");
	else if (s[i] != '\0' && s[i] == '>')
		str = ft_strdup(">");
	return (str);
}
