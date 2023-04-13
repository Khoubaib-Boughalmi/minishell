#include "../../minishell.h"


char *ft_split_data(char *str)
{
    int i;
    int start;
    int end = ft_strlen(str);

    i = 0;
    start = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] && (str[i] != '\"' && str[i] != '\''))
            break;
        if (str[i + 1] && (str[i] == '\"' || str[i] == '\'') && str[i + 1] == str[i])
            start = i + 2;
        i++;
        i++;
    }
    int j;
    j = ft_strlen(str);
    i = 0;
    while (j > 0)
    {
        if (str[j] && (str[j] != '\"' || str[j] != '\''))
            break;
        if (str[j - 1] && (str[j] == '\"' || str[j] == '\'') && str[j - 1] == str[j])
            end = j - 1;
        j--;
    }
    char *tmp;
    tmp = ft_substr(str, start, end - start);
    return tmp;
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
    char *tmp;

    i = 0;
    copy = (char *)malloc(sizeof(char) * ft_strlen(token->redirect_fname) + 1);
	ft_strlcpy(copy, token->redirect_fname, ft_strlen(token->redirect_fname) + 1);
	copy[ft_strlen(token->redirect_fname)] = '\0';
	ft_memset(token->redirect_fname, 0, ft_strlen(token->redirect_fname));
	free(token->redirect_fname);
	token->redirect_fname = NULL;
    if(expand_redirection_vars(&(token->redirect_fname), copy))
    {
        // ft_printf("IAUYIUYEIUYQWIUEYIQUWE\n");
        token->redirect_error = AMBIGUOUSERR;
        gstruct->exit_status = 1;
    }
    else
    {
        // ft_printf("asdszdsd;\n");
        i = 0;
        if(token->redirect_fname)
        {

        split_words = ft_split_qotes(token->redirect_fname, ' ');
        if(split_words[1])
        {
            int k = 0;
            int count = 0;
            while (split_words[k])
            {
                tmp = ft_split_data(split_words[k]);
                if (!tmp || tmp[0] == '\0')
                    count++;
                k++;
            }
            if (count < k - 1)
            {
                token->redirect_error = AMBIGUOUSERR;
                gstruct->exit_status = 1;
            }
            expand_quotes_red(&(token->redirect_fname));
        }
        else
        {
            char *rd_fname_copy = ft_strdup(token->redirect_fname);
            if(token->redirect_fname)
                free(token->redirect_fname);
            token->redirect_fname = trim_str(rd_fname_copy);
            expand_quotes_red(&(token->redirect_fname));
            if(rd_fname_copy)
                free(rd_fname_copy);
        }
        if(split_words)
            free_split(split_words);
        }
    }
    if(copy)
        free(copy);
}
// echo hello > $USER"hello ''$USER'' world"$USER