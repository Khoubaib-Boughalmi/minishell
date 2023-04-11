#include "../../minishell.h"

void depr_expand_quotes_red(char **original, t_token_type token_type, t_red_error *red_error)
{
	int	i = 0;
	int	j = 0;
	int	quotes;
	char	*copy;
	int flag;
	t_space has_space;
	int has_alpha;


	has_space.space_l = 0;
	has_space.space_r = 0;
	has_alpha = 0;
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
					*red_error = expand_variables_redirect(original, copy + i, NOTRIM, NOAMBG, &has_space, &has_alpha);
					i++;
					while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'' && copy[i] != '$' && copy[i] != '|') 
						i++;
				}
				else if(copy[i] != '$')
				{
					has_alpha = 1;
					if(has_space.space_r && has_alpha)
					{
						*red_error = AMBIGUOUSERR;
						gstruct->exit_status = 1;
						return ;
					}
					cbc_str_join(original, copy[i]);
					i++;
					has_space.space_l = 0;
					has_space.space_r = 0;
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
			// has_alpha = 0;
			has_space.space_l = 0;
			has_space.space_r = 0;
		}
		else
		{
			if(copy[i] == '$' && ft_isdigit(copy[i+1]))
					i += 2;
			else if(copy[i] == '$')
			{
				flag = 1;
				*red_error = expand_variables_redirect(original, copy + i, TRIM, AMBG, &has_space, &has_alpha);
				if(*red_error == AMBIGUOUSERR)
				{
					gstruct->exit_status = 1;
					return ;
				}
				if(has_alpha && has_space.space_l)
				{
					*red_error = AMBIGUOUSERR;
					gstruct->exit_status = 1;
					return ;
				}
				has_alpha = 1;
				i++;
				while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'' && copy[i] != '$')
					i++;
			}
			else
			{
				has_alpha = 1;
				if(has_space.space_r && has_alpha)
				{
					*red_error = AMBIGUOUSERR;
					gstruct->exit_status = 1;
					return ;
				}
				has_space.space_l = 0;
				has_space.space_r = 0;
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

/*
	1/ .. > $space_r"foo" = expand vars =>hello "foo boo" = split with space (only words outside of the quotes) => [hello, "foo boo"] ==> AMBIGUOUS
	2/ .. > $1_word_space_l_r'foo' = expand vars =>     hello    'foo' ==> [hello, foo] ==> AMBIGUOUS
*/
