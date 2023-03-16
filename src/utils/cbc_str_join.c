#include "../../minishell.h"

void	create_original_str(char **original)
{
	char *tmp;

	if(!(*original))
	{
		*original = (char *)malloc(sizeof(char) * 3);
		ft_memset(*original, 0, 3);
	}
	else
	{
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
}
