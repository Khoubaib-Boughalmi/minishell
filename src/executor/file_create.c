#include "../../minishell.h"

int redirect_in_file_append(char *red)
{
    int fd;

    fd = open(red, O_RDWR| O_CREAT| O_APPEND, 0666);
    if (fd < 0)
    {
        printf("minishell: No such file or directory\n");
        gstruct->exit_status = 1;
        return -1;
    }
    if (access(red, W_OK))
    {
        printf("minishell: %s: Permission denied\n", red);
        gstruct->exit_status = 1;
        return -1;
    }
    return fd;
}
int redirect_in_file(char *red)
{
    int fd;

    fd = open(red, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        printf("minishell: No such file or directory\n");
        gstruct->exit_status = 1;
        return -1;
    }
    if (access(red, W_OK))
    {
        printf("minishell: %s: Permission denied\n", red);
        gstruct->exit_status = 1;
        return -1;
    }
    return fd;
}

int redirect_out_file(char *red)
{
    int fd;

    fd = open(red, O_RDWR);
    if (fd < 0)
    {
        printf("minishell: No such file or directory\n");
        gstruct->exit_status = 1;
        return -1;
    }
    if (access(red, F_OK))
    {
        printf("minishell: %s: Permission denied\n", red);
        gstruct->exit_status = 1;
        return -1;
    }
    if (access(red, R_OK))
    {
       printf("minishell: %s: Permission denied\n", red);
       gstruct->exit_status = 1;
       return -1;
    }
    return fd;
}

int redirect_out_file_heredoc(char *red)
{
    int pip[2];
    char *str;
    char    *new_str;

    new_str = NULL;
    pipe(pip);
    dup2(gstruct->ppin, 0);
    red = ft_strjoin(red, "\n");
    // printf("%s\n", red);
    str = get_next_line(0);
    if (!str)
        return -1;
    while (1)
    {
        if(!ft_strlcmp(red, str))
            break;
        if(str[0] == '$')
        {
            str[ft_strlen(str)-1] = '\0';
            expand_variables(&new_str, str, AST_COMMAND);
            if(!new_str)
                ft_putstr_fd("\n", pip[1]);
            else
                ft_putstr_fd(ft_strjoin(new_str, "\n"), pip[1]);
            new_str = NULL;
        }
        else
            ft_putstr_fd(str, pip[1]);
        str = get_next_line(0);
    }
    close(pip[1]);
    dup2(gstruct->stin, 0);
    return pip[0];
}