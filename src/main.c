#include "../minishell.h"

t_global_struct *gstruct; //global struct

int	repl(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		if(gstruct->sigint_listener)
		{
			gstruct->sigint_listener = 0;
			exit(gstruct->exit_status);
			break;
		}
		input = get_next_line(0);
		// input = readline("$ ");
		if (!input)
		{
			free_all();
			exit(gstruct->exit_status);
		}
		input[strlen(input) - 1] = '\0';
		if(input[0] == '\0' || input[0] == '\n')
		{
			free(input);
			exit(gstruct->exit_status);
			continue;
		}
		// if (!ft_strlcmp(input, "exit"))
		// {
		// 	free(input);
		// 	break;
		// }
		add_history(input);
		tokenize_expand_execute(input); //tokenization etc
		free(input);
		}
	return (0);
}

int main(int ac, char *av[], char *envp[])
{
	(void) ac;
	(void) av;
	sig_init(SIGINT, &sigint_hander);
	sig_init(SIGQUIT, &sigquit_hander);
	if(!init_gstruct())
		return (1);
	// printf("%d\n", 9223372036854775810 & 255);
	init_envp(envp);
	repl();
	// printf("%d\n", NULL == '\0');
	return (gstruct->exit_status);
}