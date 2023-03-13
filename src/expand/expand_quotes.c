#include "../../minishell.h"

void expand_quotes(char **original, t_token_type token_type)
{
	int	i = 0;
	int	j = 0;
	char	*copy;

	copy = (char *)malloc(sizeof(char) * ft_strlen(*original) + 1);
	ft_strlcpy(copy, *original, ft_strlen(*original) + 1);
	copy[ft_strlen(*original)] = '\0';
	ft_memset(*original, 0, ft_strlen(*original));
	free(*original);
	*original = NULL;
	// char *new_or = NULL;
	// char *str = "1234567890";
	// printf("cp-%s-\n", copy);
	printf("original %s", *original);

	while(copy[i])
	{
		// if(copy[i] == '\"')
		// {
		// 	i++;
		// 	while (copy[i] && copy[i] != '\"')
		// 	{
		// 		if(copy[i] == '$')
		// 		{
		// 			// expand_variables(original, copy + i, token_type);
		// 			while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'')
		// 				i++;
		// 		}
		// 		else
		// 		{
		// 			cbc_str_join(original, copy[i]);
		// 			i++;
		// 		}
		// 	}
		// }
		// else if(copy[i] == '\'')
		// {
		// 	i++;
		// 	while (copy[i] && copy[i] != '\'')
		// 	{
		// 		cbc_str_join(original, copy[i]);
		// 		i++;
		// 	}
		// }
		// else
		// {
			// if(copy[i] == '$')
			// {
			// 	// expand_variables(original, copy + i, token_type);
			// 	while (copy[i] && copy[i] != ' ')
			// 		i++;
			// 	if(copy[i] != ' ')
			// 		i++;
			// }
			// else
			// printf("%c-\n", copy[i]);
		cbc_str_join(original, copy[i]);
		// }
	printf("original : %s\n", *original);
		i++;	
	}
	// free(copy);
}


// int main()
// {
// 	char str[] = {'h', '\"', 'e', 'l', 'l', 'o', '\"','\"','\"', '\'', '\"', ' ', '$', 'U', 'S', 'E', 'R', '\"', '\'', '\0'};
// 	expand_quotes("h\"ello\"\"\" $USER\"");
// 	return (0);
// }

// "h\"ello\"\"\" $USER\""