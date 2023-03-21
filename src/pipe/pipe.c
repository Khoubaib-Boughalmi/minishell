#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int previous_fd = 0;

void	pipelin(char ***cmd)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
	{
		printf("Error with pipe\n");
		exit (1);
	}
	if(pid < 0)
	{
		printf("Error When Forking\n");
		exit (1);
	}
	while(*cmd)
	{
		pid = fork();
		if(!pid)
		{
			dup2(previous_fd, 0);
			if(*(cmd + 1))
				dup2(fd[1], 1);
			close(fd[0]);
			execvp(*(cmd[0]), *cmd);
			exit(0);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			previous_fd = fd[0];
			cmd++;
		}
	}

} 

int main()
{
	char	*cat[] = {"cat", "-", NULL};
	char	*nl[] = {"nl", NULL};
	char	*head[] = {"head", "-10", NULL};
	char	**cmd[] = {cat, nl, head, NULL};
	pipelin(cmd);
	return (0);
}