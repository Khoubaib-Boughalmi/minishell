#include "../../minishell.h"

int previous_fd = 0;

void    pipeline(char **cmd)
{
    while(*cmd)
    {
        int    fd[2];
        pipe(fd);

        pid_t pid = fork();
        if(!pid)
        {
            dup2(previous_fd, 0);
            if(*(cmd + 1))
                dup2(fd[1], 1);
            close(fd[0]);
            system(*cmd);
            exit(0);
        }
        else
        {
            close(fd[1]);
            if (previous_fd != 0)
                close(previous_fd);
            previous_fd = fd[0];
            cmd++;
        }
    }
    while(wait(NULL) > 0);
} 

int main()
{
    pipelin((char *[]){"cat /dev/random", "nl", "head -c 200", NULL});
    return (0);
}