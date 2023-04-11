#include "../../minishell.h"

void expand_quotes_red(char **original)
{
	int	i = 0;
	int	j = 0;
	char	*copy;

	copy = (char *)malloc(sizeof(char) * ft_strlen(*original) + 1);
	ft_strlcpy(copy, *original, ft_strlen(*original) + 1);
	copy[ft_strlen(*original)] = '\0';
	memset(*original, 0, ft_strlen(*original));
	free(*original);
	*original = NULL;
	while(copy[i])
	{
		if(copy[i] == '\"')
		{
			i++;
			while (copy[i] && copy[i] != '\"')
			{
					cbc_str_join(original, copy[i]);
					i++;
			}
			if(copy[i] && copy[i] == '\"')
				i++;
		}
		else if(copy[i] == '\'')
		{
			i++;
			while (copy[i] && copy[i] != '\'')
			{
				cbc_str_join(original, copy[i]);
				i++;
			}
			if(copy[i] && copy[i] == '\'')
				i++;
		}
		else
		{
				cbc_str_join(original, copy[i]);
				i++;	 
		}
	}
	free(copy);
}

/*
	1/ .. > $space_r"foo" = expand vars =>hello "foo boo" = split with space (only words outside of the quotes) => [hello, "foo boo"] ==> AMBIGUOUS
	2/ .. > $1_word_space_l_r'foo' = expand vars =>     hello    'foo' ==> [hello, foo] ==> AMBIGUOUS
*/
