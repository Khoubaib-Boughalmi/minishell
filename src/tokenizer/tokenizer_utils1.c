#include "../../minishell.h"

int ft_count_str(char	**str)
{
	int count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	**ft_pipe_insert(char	**str)
{
	char **res;
	int i = 0;
	int j = 0;

	res = malloc((2 * ft_count_str(str) + 1) * sizeof(char *));
	while (str[i + 1])
	{
		res[j] = ft_strdup(str[i]);
		j++;
		res[j] = ft_strdup("|");
		j++;
		i++;
	}
	res[j] = ft_strdup(str[i]);
	j++;
	res[j] = 0;
	//ft_free(str);
	return (res);
}

int ft_count_der(char	**str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '<' || str[i][j] == '>')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char *ft_strdup_arg(char	*s)
{
	char	*str;
	int		i;
	int		len;

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

	while (s[len] != '<' && s[len] != '>')
	{
		len++;
	}
	j = ft_strlen(s);
	while (s[j] != '<' && s[j] != '>')
	{
		j--;
	}
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
