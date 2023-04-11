#include "../../minishell.h"

void    expand_redirection_fname(t_token *token)
{
    int     i;
	char	*copy;
    char    **split_words;

    i = 0;
    copy = (char *)malloc(sizeof(char) * ft_strlen(token->redirect_fname) + 1);
	ft_strlcpy(copy, token->redirect_fname, ft_strlen(token->redirect_fname) + 1);
	copy[ft_strlen(token->redirect_fname)] = '\0';
	ft_memset(token->redirect_fname, 0, ft_strlen(token->redirect_fname));
	free(token->redirect_fname);
	token->redirect_fname = NULL;
    expand_redirection_vars(&(token->redirect_fname), copy);
    split_words = ft_split_qotes(token->redirect_fname, ' ');
    if(split_words[1])
    {
        token->redirect_error = AMBIGUOUSERR;
        gstruct->exit_status = 1;
    }
    else
        token->redirect_error = NOERR;
}