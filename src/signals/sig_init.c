#include "../../minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	sig_init(int sig, void (*sig_handler)(int))
{
	struct sigaction act = { 0 };
	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if(sig == SIGINT)
	{
		if(sigaction(SIGINT, &act, 0) < 0)
			perror("minishell :");
	}
	else if(sig == SIGQUIT)
	{
		if(sigaction(SIGQUIT, &act, 0) < 0)
			perror("sigaction error :");
	}
}