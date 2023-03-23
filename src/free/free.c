#include "../../minishell.h"

void	free_all()
{
	free_global_struct();
}

//  total heap usage: 675 allocs, 401 frees, 228,710 bytes allocated