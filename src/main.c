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
			break;
		}
		input = readline("$ ");
		if (!input)
		{
			free_all();
			exit(EXIT_FAILURE);
		}
		if(input[0] == '\0' || input[0] == '\n')
		{
			free(input);
			continue;
		}
		if (!ft_strlcmp(input, "exit"))
		{
			free(input);
			break;
		}
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
	init_envp(envp);
	repl();
	return (0);
}