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
	// ft_export("myVar1", "myVarValue1");
	// ft_export("myVar2", "myVarValue2");
	// ft_export("myVar3", "myVarValue3");
	// ft_export("myVar4", "myVarValue4");
	// ft_env();
	// ft_unest("myVar3");
	// ft_unest("myVar1");
	// ft_unest("myVar5");
	// printf("-------------------\n");
	// ft_env();
	// ft_echo("hello world");
	ft_pwd();
	ft_cd("../../test");
	ft_pwd();

	// ft_env();
	// ft_export("newEnv", "newVal");
	// ft_unest("newEnv");
	// ft_echo("--------------\n");
	// ft_env();
	return (0);
}