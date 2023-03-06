#include "../minishell.h"

void	parse_and_execute(char *input)
{
	printf("your command : %s\n", input);
	printf("%s\n", envp_find_node(input));
}