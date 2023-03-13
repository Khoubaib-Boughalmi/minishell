#include "../../minishell.h"

void expand_quotes(char *original, t_token_type token_type)
{
	int	i = 0;
	int	j = 0;
	char	*copy;

	copy = (char *)malloc(sizeof(char) * ft_strlen(original) + 1);
	ft_strlcpy(copy, original, ft_strlen(original) + 1);
	free(original);
	while(copy[i])
	{
		if(copy[i] == '\"')
		{
			i++;
			while (copy[i] && copy[i] != '\"')
			{
				if(copy[i] == '$')
				{
					expand_variables(original, copy + i, token_type);
					while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'')
						i++;
				}
				else
				{
					printf("%c", copy[i]);
					i++;
				}
			}
		}
		else if(copy[i] == '\'')
		{
			i++;
			while (copy[i] && copy[i] != '\'')
			{
				printf("%c", copy[i]);
				i++;
			}
		}
		else
		{
			if(copy[i] == '$')
			{
				expand_variables(original, copy + i, token_type);
				while (copy[i] && copy[i] != ' ')
					i++;
				if(copy[i] != ' ')
					i++;
			}
			else
				printf("%c", copy[i]);
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