#include "../../minishell.h"

void    expand_redirection_vars(char **original, char *copy)
{
    int i;

    i = 0;
    while (copy[i])
    {
        if(copy[i] == '\'')
		{
            cbc_str_join(original, copy[i]);
			i++;
			while (copy[i] && copy[i] != '\'')
			{
				cbc_str_join(original, copy[i]);
				i++;
			}
			if(copy[i] == '\'')
            {
                cbc_str_join(original, copy[i]);
				i++;
            }
		}
        else
        {
            if(copy[i] == '$')
            {
                expand_variables_redirect(original, copy + i, NOTRIM, NOAMBG);
                i++;
                while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'' && copy[i] != '$' && copy[i] != '|' && copy[i] != '-') 
                    i++;
            }
            else
            {
                cbc_str_join(original, copy[i]);
                i++;
            }
        }
    }
}