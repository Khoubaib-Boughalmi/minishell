#include "../minishell.h"

void	parse_and_execute(char *input)
{
	printf("your command : %s\n", input);
	printf("%s\n", variable_expansion(input));
}