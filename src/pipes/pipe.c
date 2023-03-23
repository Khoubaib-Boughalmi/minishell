#include "../../minishell.h"

int previous_fd = 0;

void    pipeline(char **cmd)
{
    while(*cmd)
    {
        int    fd[2];
        // Create a pipe
        pipe(fd);

        // Create a child process
        pid_t pid = fork();
        if(!pid)
        {
            // The input of the command is the previous pipe or 0 if it's the first command
            dup2(previous_fd, 0);
            // The output of the command should go into the write end of the pipe
            if(*(cmd + 1))
                dup2(fd[1], 1);
            close(fd[0]);
            system(*cmd);
            exit(0);
        }
        else
        {
            close(fd[1]);
            // Close the file descriptor of the previous pipe when you're done with it
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