#include "../../minishell.h"

void	sigint_hander(int sig)
{
	gstruct->sigint_listener = 1;
	free(gstruct->src_input);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
    rl_redisplay();
	repl();
}

void	sigquit_hander(int sig)
{
	printf("");
}



