#include "../../minishell.h"

int	check_flags(char	*flag)
{
	int	i;

	i = 1;
	if(flag[0] != '-')
		return (0);
	
	while (flag[i] && flag[i] == 'n')
		i++;
	if(!flag[i])
		return (1);
	return (0);
}

//handle the -n flag
void	ft_echo(char	**list_vars)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if(!check_str(list_vars[1]))
		ft_printf("\n");
	else
	{
		while (check_flags(list_vars[i]))
		{
			flag = 1;
			i++;
		}
		if(!flag)
		{
			while (list_vars[i])
			{
				if(list_vars[i + 1])
					ft_printf("%s ", list_vars[i++]);
				else
					ft_printf("%s\n", list_vars[i++]);
			}
		}
		else
		{
			while (list_vars[i])
			{
				if(list_vars[i + 1])
					ft_printf("%s ", list_vars[i++]);
				else
					ft_printf("%s", list_vars[i++]);
			}
		}
	}
	gstruct->exit_status = 0;
}
		// if(ft_strlcmp(list_vars[1], "-n"))
		// {
		// 	while (list_vars[i])
		// 	{
		// 		if(list_vars[i + 1])
		// 			ft_printf("%s ", list_vars[i++]);
		// 		else
		// 			ft_printf("%s\n", list_vars[i++]);
		// 	}
		// }
		// else
		// {
		// 	i = 2;
		// 	while (list_vars[i])
		// 	{
		// 		if(list_vars[i + 1])
		// 			ft_printf("%s ", list_vars[i++]);
		// 		else
		// 			ft_printf("%s", list_vars[i++]);
		// 	}
		// }