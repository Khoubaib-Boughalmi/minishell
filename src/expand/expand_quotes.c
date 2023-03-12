#include "../../minishell.h"

void expand_quotes(char *str, t_token_type token_type)
{
	int	i = 0;
	int	j = 0;
	int	parent_q = 0; // 0 for double or no quotes ; 1 for single quotes 
	while(str[i])
	{
		if(str[i] == '\"')
		{
			i++;
			while (str[i])
			{
				// if(str[i] == '$')
				// {
				// 	expand_variables(str + i, token_type);
				// 	while (str[i] && str[i] != ' ')
				// 		i++;
				// 	if(str[i] != ' ')
				// 		i++;
				// }
				// else
				 if(str[i] == '\"')
				{
					i++;
					break;
				}
				else
					printf("%c", str[i]);
				i++;
			}
		}
		else if(str[i] == '\'')
		{
			i++;
			while (str[i])
			{
				if(str[i] == '\'')
				{
					i++;
					break;
				}
				else
					printf("%c", str[i]);
				i++;
			}
		}
		else
		{
			// if(str[i] == '$')
			// {
			// 	expand_variables(str + i, token_type);
			// 	while (str[i] && str[i] != ' ')
			// 		i++;
			// 	if(str[i] != ' ')
			// 		i++;
			// }
			// else
				printf("%c", str[i]);
			i++;	
		}
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