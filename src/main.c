#include "../minishell.h"

t_global_struct *gstruct; //global struct

int	repl(void)
{
	char	*input;

	while (1)
	{
		input = readline("$ ");
		if (!input)
			exit(EXIT_FAILURE);
		if(input[0] == '\0' || input[0] == '\n')
		{
			free(input);
			continue;
		}
		if (!strncmp(input, "exit", 5))
		{
			free(input);
			break;
		}
		parse_and_execute(input); //tokenization etc
		free(input);
	}
	return (0);
}

int main(int ac, char *av[], char *envp[])
{
	(void) ac;
	(void) av;
	if(!init_gstruct())
		return (1);
	init_envp(envp);
	// repl();
	ft_env();
	ft_export("myVar", "myVarValue");
	printf("****************************\n");
	ft_env();

	return (0);
}