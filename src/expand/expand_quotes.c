#include "../../minishell.h"

void expand_quotes(char **original, t_token_type token_type)
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
				if(copy[i] == '$' && ft_isdigit(copy[i+1]))
					i += 2;
				else if(copy[i] == '$')
				{
					expand_variables(original, copy + i, token_type);
					i++;
					while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'' && copy[i] != '$' && copy[i] != '|') 
						i++;
				}
				else if(copy[i] != '$')
				{
					cbc_str_join(original, copy[i]);
					i++;
				}
			}
			if(copy[i] == '\"')
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
			if(copy[i] == '\'')
				i++;
		}
		else
		{
			if(copy[i] == '$' && ft_isdigit(copy[i+1]))
					i += 2;
			else if(copy[i] == '$')
			{
				expand_variables(original, copy + i, token_type);
				i++;
				while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'' && copy[i] != '$')
					i++;
			}
			else
			{
				cbc_str_join(original, copy[i]);
				i++;	
			}
		}
	}
	free(copy);
}
