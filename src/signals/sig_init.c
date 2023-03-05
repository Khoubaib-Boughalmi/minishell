#include "../../minishell.h"

void	sig_init(int sig, void (*sig_handler)(int))
{
	struct sigaction	s_sig;
	s_sig.sa_handler = sig_handler;
	s_sig.sa_flags = 0;
	sigemptyset(&s_sig.sa_mask);
	if(sig == SIGINT)
	{
		if(sigaction(SIGINT, &s_sig, 0) < 0)
			perror("sigaction error :");
	}
	else if(sig == SIGQUIT)
	{
		if(sigaction(SIGQUIT, &s_sig, 0) < 0)
			perror("sigaction error :");
	}
}