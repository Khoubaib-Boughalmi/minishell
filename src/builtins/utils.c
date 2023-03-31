#include "../../minishell.h"

int	is_builtin(char	*cmd)
{
	int	i;
	char	**builtins;

	i = 0;
	
	builtins = ft_split("echo cd export unset env pwd", ' ');
	if(!builtins)
		return (0);
	while (builtins[i])
	{
		if(!ft_strlcmp(builtins[i], cmd))
		{
			free_split(builtins);
			return (1);
		}
		i++;
	}
	return (0);
}

int	list_vars_len(char **list_cmds)
{
	int	i;

	i = 0;
	while(list_cmds[i])
		i++;
	return (i);
}	

int	char_in_str(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if(str[i] == c)
			return (1);
	}
	return (0);
}

void handle_builtin(char **list_cmds)
{
	if(!ft_strlcmp(list_cmds[0], "cd"))
		ft_cd(list_cmds);
	if(!ft_strlcmp(list_cmds[0], "pwd"))
		ft_pwd();
	if(!ft_strlcmp(list_cmds[0], "echo"))
		ft_echo(list_cmds);
	if(!ft_strlcmp(list_cmds[0], "env"))
		ft_env();
	if(!ft_strlcmp(list_cmds[0], "export"))
	{
		// int	i = 0;
		// while (list_cmds[i])
		// {
		// 	printf("%s\n", list_cmds[i]);
		// 	i++;
		// }
		
		ft_export_with_args(list_cmds);

	}
	if(!ft_strlcmp(list_cmds[0], "unset"))
		ft_unest(list_cmds);
	
}

