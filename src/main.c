/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:51:33 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/12 09:42:55 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global_struct	*g_struct;

int	repl(void)
{
	// char	*input;

	// input = NULL;
	// while (1)
	// {
	// 	input = get_next_line(0);
	// 	if (!input)
	// 	{
	// 		exit(g_struct->exit_status);
	// 	}
	// 	if (input[strlen(input) - 1] == '\n')
	// 		input[strlen(input) - 1] = '\0';
	// 	if (input[0] == '\0')
	// 	{
	// 		free(input);
	// 		continue ;
	// 	}
	// 	tokenize_expand_execute(input);
	// 	free(input);
	// 	// system("leaks minishell");
	// }
	// return (g_struct->exit_status);
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("$ ");
		if (!input)
		{
			exit(g_struct->exit_status);
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokenize_expand_execute(input);
		free(input);
	}
	return (g_struct->exit_status);
}

int	main(int ac, char *av[], char *envp[])
{
	(void) ac;
	(void) av;
	sig_init(SIGINT, &sigint_hander);
	signal(SIGQUIT, SIG_IGN);
	if (!init_g_struct())
		return (1);
	init_envp(envp);
	repl();
	return (g_struct->exit_status);
}
