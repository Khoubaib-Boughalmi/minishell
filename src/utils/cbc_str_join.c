#include "../../minishell.h"

void	create_original_str(char **original)
{
	char *tmp;

	if(!(*original))
	{
		printf("from here\n");
		*original = (char *)malloc(sizeof(char) * 2);
		ft_memset(*original, 0, 2);
	}
	else
	{
		printf("from second here\n");
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
	if(!*original || !(ft_strlen(*original) % 2))
		create_original_str(original);	
	(*original)[ft_strlen(*original)] = c;
	printf("string : %s\n", (*original));

}


int main()
{
	char *str = NULL;
	cbc_str_join(&str, 'A');
	cbc_str_join(&str, 'B');
	cbc_str_join(&str, 'C');
	cbc_str_join(&str, 'D');
	cbc_str_join(&str, 'E');
	cbc_str_join(&str, 'F');
	cbc_str_join(&str, 'G');
	cbc_str_join(&str, '1');
	cbc_str_join(&str, '2');
	cbc_str_join(&str, '3');
	cbc_str_join(&str, '4');
	cbc_str_join(&str, '5');
	cbc_str_join(&str, '6');
	cbc_str_join(&str, '7');

	return (0);
}