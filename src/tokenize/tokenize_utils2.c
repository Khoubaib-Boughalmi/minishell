#include "../../minishell.h"

int ft_check_der(char *str)
{
	int j = 0;
	while (str[j])
	{
		if (str[j] == '>' || str[j] == '<')
			return 1;
		j++;
	}
	return 0;
}

int ft_check_pipe(char *str)
{
	int j = 0;
	while (str[j])
	{
		if (str[j] == '|')
			return 1;
		j++;
	}
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

char	**ft_split_der(char	**str)
{
	char **res;
	char **tmp;
	int i = 0;
	int j = 0;

	res = malloc((ft_count_str(str) + ft_count_der(str) + 2) * sizeof(char *));
	while (i < ft_count_str(str))
	{
		if (ft_check_der(str[i]))
		{
			res[j] = ft_strdup_arg(str[i]);
			j++;
			res[j] = ft_strdup_der(str[i]);
			j++;
			res[j] = ft_strdup_file(str[i]);
			j++;
		}
		else
		{
			res[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	res[j] = 0;
	//ft_free(str);
	return (res);
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
