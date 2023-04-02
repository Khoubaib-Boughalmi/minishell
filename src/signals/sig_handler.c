#include "../../minishell.h"

void	sigint_hander(int sig)
{    
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_hander_executor(int sig)
{    
	(void)sig;
	dup2(gstruct->ppout, 1);
	dup2(gstruct->ppin, 0);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	// rl_redisplay();
}

void	sigquit_hander(int sig)
{
	printf("heeeeeeeeeeeeeeeeeeeeeeeeeeelp\n");
	free_all();
}



//205,558 bytes in 274 blocks
