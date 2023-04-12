#include "../../minishell.h"

int is_skippable(char   *str)
{
    int i;

    i = 0;
    if(!str)
        return (0);
    if(!str[i])
        return (0);
    while (str[i])
    {
        if(str[i] == '\"' || str[i] == '\'')
        {
            if (str[i] != str[i + 1])
                return 1;
        }
        i++;
    }
    
    return (0);
}

// int split_words_len(char **arr)
// {
//     int i;

//     i = 0;
//     while (is_skippable[arr[i]])

//         i++;
//     return    
// }

void    expand_redirection_fname(t_token *token)
{
    int     i;
	char	*copy;
    char    **split_words;
    char    *split_words_str;

    i = 0;
    copy = (char *)malloc(sizeof(char) * ft_strlen(token->redirect_fname) + 1);
	ft_strlcpy(copy, token->redirect_fname, ft_strlen(token->redirect_fname) + 1);
	copy[ft_strlen(token->redirect_fname)] = '\0';
	ft_memset(token->redirect_fname, 0, ft_strlen(token->redirect_fname));
	free(token->redirect_fname);
	token->redirect_fname = NULL;
    if(expand_redirection_vars(&(token->redirect_fname), copy))
    {
        // ft_printf("1\n");
        token->redirect_error = AMBIGUOUSERR;
        gstruct->exit_status = 1;
    }
    else
    {
        i = 0;
        split_words = ft_split_qotes(token->redirect_fname, ' ');
        if(split_words[1])
        {
            int k = 0;
            int count = 0;
            while (split_words[k])
            {
                if (!is_skippable(split_words[k]))
                    count++;
                k++;
            }
            if(count <= k)
            {
                token->redirect_error = AMBIGUOUSERR;
                gstruct->exit_status = 1; 
            }
        //     expand_quotes_red(&(token->redirect_fname));
        }
        // else
        // {
            char *rd_fname_copy = ft_strdup(token->redirect_fname);
            if(token->redirect_fname)
                free(token->redirect_fname);
            token->redirect_fname = trim_str(rd_fname_copy);
            expand_quotes_red(&(token->redirect_fname));
            if(rd_fname_copy)
                free(rd_fname_copy);
        // }
        if(split_words)
            free_split(split_words);
    }
    if(copy)
        free(copy);
}
// echo hello > $USER"hello ''$USER'' world"$USER