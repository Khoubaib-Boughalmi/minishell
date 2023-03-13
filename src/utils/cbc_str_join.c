#include "../../minishell.h"

void	create_original_str(char **original)
{
	char *tmp;

	if(!(*original))
	{
		printf("from first\n");
		*original = (char *)malloc(sizeof(char) * 2);
		ft_memset(*original, 0, 2);
	}
	else
	{
		printf("from second\n");
		tmp = (char *)malloc(sizeof(char) * ft_strlen(*original) + 1);
		ft_memset(tmp, 0, ft_strlen(*original) + 1);
		ft_strlcpy(tmp, *original, ft_strlen(*original) + 1);
		free(*original);
		*original = (char *)malloc(sizeof(char) * (ft_strlen(tmp) * 2) + 1);
		ft_memset(*original, 0, (ft_strlen(tmp) * 2) + 1);
		ft_strlcpy(*original, tmp, ft_strlen(tmp) + 1);
		free(tmp);
	}
}

void cbc_str_join(char **original, char c)
{
	if(!*original)
	{
		printf("first entered\n");
		create_original_str(original);	
	}
	else if(!(ft_strlen(*original) % 2))
	{
		printf("second entered\n");
		create_original_str(original);	
	}
	printf("len :%ld\n", strlen((char *)*original));
	(*original)[ft_strlen(*original)] = c;
	// printf("string : %s\n", (*original));
}


// int main()
// {
// 	char *str = NULL;
// 	char *copy = "hello world";
// 	int i = 0;
// 	while(copy[i])
// 	{
// 		cbc_str_join(&str, copy[i]);
// 		i++;
// 	}

// 	return (0);
// }