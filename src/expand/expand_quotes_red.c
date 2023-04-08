#include "../../minishell.h"

void expand_quotes_red(char **original, t_token_type token_type, t_red_error *red_error)
{
	int	i = 0;
	int	j = 0;
	int	quotes;
	char	*copy;
	int flag;

	flag = 0;
	quotes = 0;
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
			quotes = 1;
			i++;
			while (copy[i] && copy[i] != '\"')
			{
				if(copy[i] == '$' && ft_isdigit(copy[i+1]))
					i += 2;
				else if(copy[i] == '$')
				{
					*red_error = expand_variables_redirect(original, copy + i, NOTRIM, NOAMBG);
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
				flag = 1;
				*red_error = expand_variables_redirect(original, copy + i, TRIM, AMBG);
				if(*red_error == AMBIGUOUSERR)
				{
					gstruct->exit_status = 1;
					return ;
				}
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
	if((!original || !original[0]) && flag == 1)
		*red_error = AMBIGUOUSERR;
	// else if(((!original || !original[0]) && !quotes) || (char_in_str(*original, ' ')))
	// 	*red_error = AMBIGUOUSERR;
	// else
	// 	*red_error = NOERR;
}
