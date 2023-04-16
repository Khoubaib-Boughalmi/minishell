// #include "../../minishell.h"

// int expand_redirection_vars(char **original, char *copy)
// {
//     int i;
//     int vars;

//     i = 0;
//     vars = 1;
//     int skip;

//     skip = 0;
//     while (copy[i])
//     {
//         if(copy[i] == '\'')
// 		{
//             // cbc_str_join(original, copy[i]);
// 			i++;
// 			while (copy[i] && copy[i] != '\'')
// 			{
// 				cbc_str_join(original, copy[i]);
// 				i++;
// 			}
// 			if(copy[i] == '\'')
//             {
//                 // cbc_str_join(original, copy[i]);
// 				i++;
//             }
// 		}
//         else
//         {
//             if(copy[i] == '$' && (ft_isdigit(copy[i+1]) || copy[i+1] == '@'))
// 				i += 2;
//             else if(copy[i] == '$')
//             {
//                 vars = 1;
//                 expand_variables_redirect(original, copy + i, NOTRIM, NOAMBG);
//                 i++;
//                 while (copy[i] && copy[i] != ' ' && copy[i] != '\"' && copy[i] != '\'' && copy[i] != '$' && copy[i] != '|' && copy[i] != '-') 
//                     i++;
//             }
//             else
//             {
//                 cbc_str_join(original, copy[i]);
//                 i++;
//             }
//         }
//     }
//     if(vars && !(*original))
//         return (1);
//     char    *original_cpy = ft_strdup(*original);
//     if(original_cpy)
//     {
//         expand_quotes_red(&original_cpy);
//         i = 0;
//         if(original_cpy)
//         {
//             while (original_cpy[i] && original_cpy[i] == ' ')
//                 i++;
//             if(!original_cpy[i])
//                 return (1);
//         }
//     }
//     return (0);
// }













#include "../../minishell.h"

int expand_redirection_vars(char **original, char *copy)
{
    int i;
    int vars;

    i = 0;
    vars = 0;
    int single_q = 0;

    while (copy[i])
    {
        if(copy[i] == '\'')
		{
            // cbc_str_join(original, copy[i]);
			i++;
			while (copy[i] && copy[i] != '\'')
			{
				cbc_str_join(original, copy[i]);
				i++;
			}
			if(copy[i] == '\'')
            {
                // cbc_str_join(original, copy[i]);
				i++;
            }
		}
        else if(copy[i] == '\"')
        {
            cbc_str_join(original, copy[i]);
            i++;
            while (copy[i] && copy[i] != '\"')
            { 
                if(copy[i] == '$' && ft_isdigit(copy[i+1]))
                    i += 2;
                else if(copy[i] == '$')
                {
                    //this is too general make a case for when inside double quotes and outside
                    vars = 1;
                    expand_variables_redirect(original, copy + i, TRIM, NOAMBG);
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
            if(copy[i] == '\"')
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
                expand_variables_redirect(original, copy + i, TRIM, NOAMBG);
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
    {
        // ft_printf("hihihi %s\n", *original);
        return (1);

    }
    // if(*original)
    // {
        char    *original_cpy = ft_strdup(*original);
        // ft_printf("here\n");
        if(original_cpy)
        {
            // ft_printf("%s\n", original_cpy);
            expand_quotes_red(&original_cpy);
            i = 0;
            if(original_cpy)
            {
                while (original_cpy[i] && original_cpy[i] == ' ')
                    i++;
                if(!original_cpy[i])
                    return (1);
            }
        }
    // }
    return (0);
}