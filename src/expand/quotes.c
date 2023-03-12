#include "../../minishell.h"

// args[0] : "e"c"ho" 
// args[1] :"hello $USER"


void expand_quotes(char *arg)
{
	int	i = 0;
	int	parent_q = 0; // 0 for double or no quotes ; 1 for single quotes 
	while(arg[i])
	{
		if(arg[i] == '\"')
		{
			i++;
			while (arg[i])
			{
				if(arg[i] == '$')
					printf("9");
				else if(arg[i] == '\"')
				{
					i++;
					break;
				}
				else
					printf("%c", arg[i]);
				i++;
			}
		}
		else if(arg[i] == '\'')
		{
			i++;
			while (arg[i])
			{
				if(arg[i] == '\'')
				{
					i++;
					break;
				}
				else
					printf("%c", arg[i]);
				i++;
			}
			printf(".");
		}
		else
		{
			if(arg[i] == '$')
				printf("9");
			else
				printf("%c", arg[i]);
			i++;	
		}
	}
}


int main()
{
	char str[] = {'h', '\"', 'e', 'l', 'l', 'o', '\"','\"','\"', '\'', '\"', ' ', '$', 'U', 'S', 'E', 'R', '\"', '\'', '\0'};
	expand_quotes(str);
	return (0);
}

// h"ello"'" $USER"'