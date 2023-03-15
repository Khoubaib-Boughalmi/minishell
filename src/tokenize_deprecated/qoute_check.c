#include "../../minishell.h"

int ft_count_cotes(char *str,int start,int end)
{
	int count = 0;

	while (start < end)
	{
		if (str[start] == '\"' || str[start] == '\'')
			count++;
		start++;
	}
	return count;
}

char	*ft_first_arg(char *str)
{
	int i = 0;
	char *result;
	int end = 0;
	int start = 0;
	int check = -1;

	while (str[end])
	{
		if (str[end] != ' ')
			check = 1;
		if (check == 1 && str[end] == ' ')
			break;
		end++;
	}
	while (str[start])
	{
		if (str[start] != ' ')
			break;
		start++;
	}
	i = 0;
	if (ft_count_cotes(str, start, end) % 2 != 0)
	{
		printf("Error u need to have 2qoute\n");
		exit(0);
	}
	result = malloc(ft_strlen(str) - ft_count_cotes(str, start, end) + 1);
	while (start < end)
	{
		if (str[start] != '\"' && str[start] != '\'')
		{
			result[i] = str[start];
			i++;
		}
		start++;
	}
	while (str[end])
	{
		result[i] = str[end];
		end++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

int ft_count_spaces(char *str)
{
    int i = 0;
    int flg;
	int count = 0;

	while (str[i])
	{
		if (str[i] == ' ')
			flg = 1;
		if (!(str[i] == ' '))
		{
			if (flg)
				count++;
            count++;
			flg = 0;
		}
		i++;
	}
	return count - 1;
}

char *ft_egnore_space(char *str)
{
    int i = 0;
    int j = 0;
    int flg;
    char *result;

	result = malloc(ft_count_spaces(str) + 1);
	while (str[i] == ' ')
		i += 1;
	while (str[i])
	{
		if (str[i] == ' ')
			flg = 1;
		if (!(str[i] == ' '))
		{
			if (flg)
            {
				result[j] = ' ';
                j++;
            }
			flg = 0;
			result[j] = str[i];
            j++;
		}
		i += 1;
	}
    result[j] = '\0';
    return result;
}

char	**ft_args_split(char *str)
{
	char **result;
	char	c;
	int		i;

	i = 0;
	c = 0;
	str = ft_first_arg(str);
    str = ft_strtrim(str, " ");
    str = ft_egnore_space(str);
	result = ft_split_qotes(str, ' ');
	return (result);
}
