#include "../minishell.h"

int	init_gstruct(char *input)
{
	//initialize everything with 0
	gstruct = (t_global_struct *)malloc(sizeof(t_global_struct));
	if (!gstruct)
		return (0);
	ft_memset(gstruct, 0, sizeof(t_global_struct));
	//save the user original command in global struct
	gstruct->src_input = input;
	return (1);
}