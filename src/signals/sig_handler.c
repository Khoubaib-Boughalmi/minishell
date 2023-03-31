#include "../../minishell.h"

void	sigint_hander(int sig)
{    
	(void)sig;
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	sigquit_hander(int sig)
{
	printf("heeeeeeeeeeeeeeeeeeeeeeeeeeelp\n");
	free_all();
}



//205,558 bytes in 274 blocks
