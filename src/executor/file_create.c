#include "../../minishell.h"

int redirect_in_file_append(char *red)
{
    int fd;

    fd = open(red, O_RDWR| O_CREAT| O_TRUNC, 0666);
    return fd;
}
int redirect_in_file(char *red)
{
    int fd;

    fd = open(red, O_RDWR | O_CREAT, 0666);
    return fd;
}

int redirect_out_file(char *red)
{
    int fd;

    fd = open(red, O_RDWR);
    if (!fd)
        return 0;
    return fd;
}

int redirect_out_file_heredoc(char *red)
{
    int pip[2];
    char *str;

    pipe(pip);
    // printf("red %s\n", red); 
    red = ft_strjoin(red, "\n");
    str = get_next_line(0);
    if (!str)
        return 0;
    while (1)
    {
        if(!ft_strlcmp(red, str))
            break;
        ft_putstr_fd(str, pip[1]);
        str = get_next_line(0);
    }
    close(pip[1]);

    return pip[0];
}