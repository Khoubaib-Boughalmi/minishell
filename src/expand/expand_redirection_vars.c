#include "../../minishell.h"

int expand_redirection_vars(char **original, char *copy)
{
    int i;
    int vars;

    i = 0;
    vars = 1;
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
            if(copy[i] == '$' && (ft_isdigit(copy[i+1]) || copy[i+1] == '@'))
				i += 2;
            else if(copy[i] == '$')
            {
                //this is too general make a case for when inside double quotes and outside
                vars = 1;
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
    if(vars && !(*original))
        return (1);
    return (0);
}