#include "../../minishell.h"

void	sigint_hander(int sig)
{
	if(rl_line_buffer[0] == '\0')
		printf("heeeeeeeeeeeeeeeeeeeeeeeeeeelp\n");

	// gstruct->sigint_listener = 1;
	// free(gstruct->src_input);
	// printf("\n");
	// rl_replace_line("", 0);
	// rl_on_new_line();
   //  rl_redisplay();
	// repl();
}

void	sigquit_hander(int sig)
{
	printf("heeeeeeeeeeeeeeeeeeeeeeeeeeelp\n");
	free_all();
}



//205,558 bytes in 274 blocks
