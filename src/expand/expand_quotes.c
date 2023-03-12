#include "../../minishell.h"

void expand_quotes(char *str, t_token_type token_type)
{
	int	i = 0;
	int	j = 0;
	char	*str_cpy;

	str_cpy = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	ft_strlcpy(str_cpy, str, ft_strlen(str) + 1);
	printf("copy : %s\n", str_cpy);

	while(str_cpy[i])
	{
		if(str_cpy[i] == '\"')
		{
			i++;
			while (str_cpy[i] && str_cpy[i] != '\"')
			{
				if(str_cpy[i] == '$')
				{
					expand_variables(str_cpy + i, token_type);
					while (str_cpy[i] && str_cpy[i] != ' ' && str_cpy[i] != '\"' && str_cpy[i] != '\'')
						i++;
				}
				else
				{
					printf("%c", str_cpy[i]);
					i++;
				}
			}
		}
		else if(str_cpy[i] == '\'')
		{
			i++;
			while (str_cpy[i] && str_cpy[i] != '\'')
			{
				printf("%c", str_cpy[i]);
				i++;
			}
		}
		else
		{
			if(str_cpy[i] == '$')
			{
				expand_variables(str_cpy + i, token_type);
				while (str_cpy[i] && str_cpy[i] != ' ')
					i++;
				if(str_cpy[i] != ' ')
					i++;
			}
			else
				printf("%c", str_cpy[i]);
		}
		i++;	
	}
	printf("\n");
}


// int main()
// {
// 	char str[] = {'h', '\"', 'e', 'l', 'l', 'o', '\"','\"','\"', '\'', '\"', ' ', '$', 'U', 'S', 'E', 'R', '\"', '\'', '\0'};
// 	expand_quotes("h\"ello\"\"\" $USER\"");
// 	return (0);
// }

// "h\"ello\"\"\" $USER\""